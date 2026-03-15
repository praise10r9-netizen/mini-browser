#include <stdio.h>
#include <unistd.h>
#include "../include/net.h"
#include "../include/http.h"
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
  const char* host = "httpbin.org";
  const char* path = "/";
  
  int sock = connect_to_host(host, 80);
  
  if(sock < 0)
    return 1;
    
  http_get(sock, host, path);
  
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
