#include "../include/utils.h"
#include <cstdio>
#include <netinet/in.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

void serv_handle_conn(int sockfd) {
  while (true) {
    char buf[1024];
    bzero(buf, sizeof(buf));

    ssize_t read_bytes = read(sockfd, buf, sizeof(buf));

    if (read_bytes > 0) {
      printf("msg from client: %s\n", buf);
      write(sockfd, buf, read_bytes);
    } else if (read_bytes == 0) { // read返回0，表示EOF
      printf("disconnect form client socket: %d", sockfd);
      close(sockfd);
      break;
    } else if (read_bytes ==
               -1) { // read返回-1，表示发生错误，按照上文方法进行错误处理
      close(sockfd);
      errif(true, "socket read error");
    }
  }
}

int main() {
  struct sockaddr_in serv_addr;
  int sockfd = init_socket(&serv_addr, true);

  int clnt_fd = accept_conn(sockfd);

  serv_handle_conn(clnt_fd);

  return 0;
}