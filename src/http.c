#include "../include/http.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void http_get(int socket, const char* host, const char* path)
{
  char request[1024];
  
  snprintf(request,sizeof(request), "GET %s HTTP/1.1\r\n"
				    "Host: %s\r\n"
  				    "User-Agent: MiniBrowser/0.1\r\n"
 				    "Connection: close\r\n"
  				    "\r\n",path,host);
  
  send(socket, request, strlen(request), 0);
}
