#include "../include/utils.h"
#include <netinet/in.h>

int main() {
  struct sockaddr_in serv_addr;
  int sockfd = init_socket(&serv_addr, true);

  int clnt_fd = accept_conn(sockfd);
  return 0;
}