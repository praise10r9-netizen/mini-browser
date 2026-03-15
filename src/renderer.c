#include "../include/renderer.h"
#include <stdio.h>
#include <string.h>

void render_dom(DOMNode *node)
{
  if(!node)
    return;
    
  if(node->type == NODE_TEXT)
  {
    printf("%s", node->text);
  }
  
  if(node->type == NODE_ELEMENT)
  {
    if(strcmp(node->tag, "h1")==0)
    {
       printf("\n\n");
    }
    if(strcmp(node->tag, "p")==0)
    {
      printf("\n");
    }
    if(strcmp(node->tag, "br")==0)
    {
      printf("\n");
    }
   }
    DOMNode *child = node->first_child;
    
    while(child)
    {
      render_dom(child);
      child = child->next_sibling;
    }
    if(node->type == NODE_ELEMENT)
    {
      if(strcmp(node->tag, "h1") == 0)
        printf("\n");
        
      if(strcmp(node->tag, "p") == 0)
        printf("\n");
    }
}
