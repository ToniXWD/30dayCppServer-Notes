
#include "../include/utils.h"
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
  struct sockaddr_in serv_addr;

  int sockfd = init_socket(&serv_addr, false);

  int res = connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr));
}
