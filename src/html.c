#include "../include/html.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 256

DOMNode* parse_html(const char* html)
{
  DOMNode* stack[STACK_SIZE];
  int top = -1;
  
  DOMNode* root = create_element("document");
  stack[++top] = root;
  
  const char *p = html;
  
  while(*p)
  {
    if(*p == '<')
    {
      if(*(p+1) == '/')
      {
        char* end = strchr(p, '>');
        
        if(!end)
           break;
        if(top > 0)
            top--;
        
        p = end + 1;
      } else
      {
        char tag[64] = {0};
        int i = 0;
        
        p++;
        while(*p && *p != '>' && *p != ' ' && i < 63)
           tag[i++] = *p++;
           
        tag[i] = '\0';
        DOMNode *node = create_element(tag);
        
        append_child(stack[top], node);
        char* end = strchr(p, '>');
        if (!end) break;
        
        if(top + 1 >= STACK_SIZE)
        {
           printf("HTML nesting too deep\n");
           return root;
        }
        
        stack[++top] = node;
        
        p = end + 1; 
      }
    }else
    {
      char text[256];
      int i = 0;
      
      while(*p && *p != '<' && i<sizeof(text) - 1)
        text[i++] = *p++;
        
       text[i] = '\0';
       
       if(strspn(text, "\t\n\r") != strlen(text))
       {
         DOMNode *node = create_text(text);
         append_child(stack[top],node);
       }
    }
  }
  return root;
}
