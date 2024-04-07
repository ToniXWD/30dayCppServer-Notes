#include "../include/utils.h"
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_EVENTS 1024
#define READ_BUFFER 4

void add_fd_to_ev(struct epoll_event *ev, int fd, bool is_et,
                  bool is_non_block) {
  bzero(ev, sizeof(*ev));
  ev->events = EPOLLIN;
  ev->data.fd = fd;

  if (is_et) {
    ev->events |= EPOLLET;
  }

  if (is_non_block) {
    int res = fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
    errif(res == -1, "fcntl failed");
  }
}

void add_fd_to_epoll(int epfd, int sockfd, struct epoll_event *ev) {
  int res = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, ev);
  errif(res == -1, "epoll_ctl failed");
}

void serv_handle_conn(int sockfd) {
  char buf[READ_BUFFER];

  while (
      true) { //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
    bzero(buf, sizeof(buf));

    ssize_t read_bytes = read(sockfd, buf, sizeof(buf));

    if (read_bytes > 0) {
      printf("msg from client: %s\n", buf);
      write(sockfd, buf, read_bytes);
    } else if (read_bytes == 0) { // read返回0，表示EOF
      printf("disconnect form client socket: %d", sockfd);
      close(sockfd);
      break;
    } else if (read_bytes == -1 && errno == EINTR) { // 客户端正常中断、继续读取
      printf("continue reading");
      continue;
    } else if (read_bytes == -1 &&
               ((errno == EAGAIN) ||
                (errno ==
                 EWOULDBLOCK))) { //非阻塞IO，这个条件表示数据全部读取完毕
      printf("finish reading once, errno: %d\n", errno);
      break;
    } else if (read_bytes == 0) {
      printf("EOF, client fd %d disconnected\n", sockfd);
      close(sockfd); //关闭socket会自动将文件描述符从epoll树上移除
      break;
    }
  }
}

int main() {
  struct sockaddr_in serv_addr;
  int sockfd = init_socket(&serv_addr, true);

  // 创建 epoll 的文件描述符
  int epfd = epoll_create1(0);
  errif(epfd == -1, "epoll_create failed");

  // 创建并设置事件
  struct epoll_event events[MAX_EVENTS], ev;
  add_fd_to_ev(&ev, sockfd, false, true);

  //将服务器socket fd添加到epoll
  add_fd_to_epoll(epfd, sockfd, &ev);

  while (true) {
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);

    for (int idx = 0; idx < nfds; idx++) {
      if (events[idx].data.fd == sockfd) {
        int clnt_fd = accept_conn(sockfd);
        add_fd_to_ev(&ev, clnt_fd, true, true);
        add_fd_to_epoll(epfd, clnt_fd, &ev);
      } else if (events[idx].events & EPOLLIN) {
        serv_handle_conn(events[idx].data.fd);
      } else { //其他事件，之后的版本实现
        printf("something else happened\n");
      }
    }
  }

  close(sockfd);
  return 0;
}