
#include "../include/utils.h"
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void cln_handle_conn(int sockfd) {
  while (true) {
    char buf[1024];
    bzero(buf, sizeof(buf));

    scanf("%s", buf);

    ssize_t write_bytes = write(sockfd, buf, strlen(buf));

    if (write_bytes ==
        -1) { // read返回-1，表示发生错误，按照上文方法进行错误处理
      close(sockfd);
      errif(true, "socket read error");
    }

    bzero(buf, sizeof(buf));
    ssize_t read_bytes = read(sockfd, buf, sizeof(buf));

    if (read_bytes > 0) {
      printf("msg from server: %s\n", buf);
    } else if (read_bytes ==
               0) { // read返回0，通常是服务器断开链接，等会儿进行测试
      printf("disconnect form server socket: %d", sockfd);
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

  int sockfd = init_socket(&serv_addr, false);

  int res = connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr));
  errif(res == -1, "connect error");

  cln_handle_conn(sockfd);
}
