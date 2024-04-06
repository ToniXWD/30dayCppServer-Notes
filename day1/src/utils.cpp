#include "../include/utils.h"

int init_socket(struct sockaddr_in *serv_addr, bool is_server) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(serv_addr, sizeof(*serv_addr));
  serv_addr->sin_family = AF_INET;
  serv_addr->sin_addr.s_addr = inet_addr("0.0.0.0");
  serv_addr->sin_port = htons(7921);

  if (!is_server) {
    return sockfd;
  }

  int res = bind(sockfd, (sockaddr *)serv_addr, sizeof(*serv_addr));
  if (res != 0) {
    exit(-1);
  }

  res = listen(sockfd, SOMAXCONN);
  if (res != 0) {
    exit(-1);
  }
  return sockfd;
}

int accept_conn(int sockfd) {
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_len = sizeof(clnt_addr);
  bzero(&clnt_addr, clnt_addr_len);

  int clnt_sockfd = accept(sockfd, (sockaddr *)&clnt_addr, &clnt_addr_len);

  printf("new client fd %d! IP: %s Port: %d\n", clnt_sockfd,
         inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
  return clnt_sockfd;
}