#include "../include/url.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_url(const char* input, URL* url)
{
  memset(url, 0, sizeof(URL));
  
  const char* scheme_end = strstr(input, "://");
  
  if(!scheme_end)
  	return -1;
  	
  int scheme_len = scheme_end - input;
  strncpy(url->scheme, input, scheme_len);
  
  const char* host_start = scheme_end + 3;
  
  const char* path_start = strchr(host_start, '/');
  
  if(!path_start)
  {
     strcpy(url->path, "/");
     path_start = input + strlen(input);
  }else
  {
    strcpy(url->path, path_start);
  }
  
  int host_len = path_start - host_start;
  
  char host_port[256];
  strncpy(host_port, host_start, host_len);
  
  host_port[host_len] = 0;
  
  char* port_ptr = strchr(host_port, ':');
  
  if(port_ptr)
  {
    *port_ptr = 0;
    strcpy(url->host, host_port);
    url->port = atoi(port_ptr + 1);
  }else
  {
    strcpy(url->host, host_port);
    if(strcmp(url->scheme,"http") == 0)
    	url->port = 80;
    else if(strcmp(url->scheme, "https") ==0)
    	url->port = 443;
    else
    	return -1;
  }
  return 0;
  
}
