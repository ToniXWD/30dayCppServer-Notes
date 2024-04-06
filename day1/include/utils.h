#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>

int init_socket(struct sockaddr_in *serv_addr, bool is_server);
int accept_conn(int sockfd);