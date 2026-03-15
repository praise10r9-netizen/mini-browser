#ifndef URL_H
#define URL_H

typedef struct
{
  char scheme[16];
  char host[256];
  int port;
  char path[1024];
}URL;

int parse_url(const char* input, URL *url);

#endif
