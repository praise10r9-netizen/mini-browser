#include "../include/net.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>

int connect_to_host(const char *host, int port)
{
  struct hostent *server;
  struct sockaddr_in serv_addr;
  
  int sock = socket(AF_INET,SOCK_STREAM,0);
  
  if(sock < 0)
  {
    perror("socket()");
    return -1;
  }
  
  server = gethostbyname(host);
  
  if(server == NULL)
  {
     fprintf(stderr, "ERROR: no such host\n");
     return -1;
  }
  
  memset(&serv_addr, 0, sizeof(serv_addr));
  
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  
  serv_addr.sin_port = htons(port);
  
  if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("connect()");
    return -1;
  }
  return sock;
}
