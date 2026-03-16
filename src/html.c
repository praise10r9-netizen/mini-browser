#include "../include/html.h"
#include "../include/dom.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 256
static const char* parse_attributes(const char* p,DOMNode* node)
{
   while(*p && *p != '>')
   {
      while(*p == ' ')
        p++;
      if(*p == '>' || *p == '/')
        break;
        
      char name[64] = {0};
      char value[256] = {0};
      
      int i = 0;
      
      while(*p && *p != '=' && *p != '>' && *p != ' ')
        name[i++] = *p++;
        
     name[i] = '\0';
     
     while(*p == ' ')
       p++;
       
    if(*p == '=')
       p++;
       
    while(*p == ' ')
       p++;
       
    if(*p == '"' || *p == '\'')
    {
      char quote = *p++;
      i = 0;
      
      while(*p && *p != quote && i < 255)
         value[i++] = *p++;
         
      value[i] = '\0';
      
     if(*p == quote)
       p++;
    }
    if(strlen(name) > 0)
       add_attribute(node,name, value);  
       
    while(*p == ' ')
     p++;
   }
   return p;
}
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
      if(strncmp(p, "</", 2)==0)
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
        while(*p && *p != '>' && *p != ' ' && *p != '/' && i < 63)
           tag[i++] = *p++;
           
        tag[i] = '\0';
        DOMNode *node = create_element(tag);
        p = parse_attributes(p,node);
        
        append_child(stack[top], node);
        char* end = strchr(p, '>');
       if(!end)
         {break;}
         
         p = end + 1;
        
        if(top + 1 >= STACK_SIZE)
        {
           printf("HTML nesting too deep\n");
           return root;
        }
        
        stack[++top] = node;
        
        p = strchr(p, '>');
        if(!p) break;
        p++;
      }
      
    }else
    {
      char text[256];
      int i = 0;
      
      while(*p && *p != '<' && i<sizeof(text) - 1)
        text[i++] = *p++;
        
       text[i] = '\0';
       
       if(strspn(text, " \t\n\r") != strlen(text))
       {
         DOMNode *node = create_text(text);
         append_child(stack[top],node);
       }
    }
  }
  return root;
}
