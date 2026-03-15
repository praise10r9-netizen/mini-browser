#include <stdio.h>
#include <unistd.h>
#include "../include/net.h"
#include "../include/http.h"
#include "../include/url.h"
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[])
{

  if(argc < 2)
  {
    printf("usage: %s <url>\n",argv[0]);
    return 1;
  }
  
  URL url;
  
  if(parse_url(argv[1], &url) != 0)
  {
    printf("Invalid URL\n");
  }
  
  printf("scheme: %s\n", url.scheme);
  printf("Host: %s\n", url.host);
  printf("Port: %d\n", url.port);
  printf("Path: %s\n", url.path);
  
  int sock = connect_to_host(url.host, url.port);
  
  if(sock < 0)
    return 1;
    
  http_get(sock, url.host, url.path);
  
  char buffer[4096];
  int bytes;
  
  while((bytes = recv(sock, buffer, sizeof(buffer)-1, 0)) > 0)
  {
     buffer[bytes] = 0;
     printf("%s", buffer);
  }
  
  close(sock);
  
  return 0;
}
