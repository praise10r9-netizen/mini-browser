#include "../include/extractor.h"
#include <stdio.h>
#include <string.h>
#include "../include/dom.h"

 
 static int is_tag(DOMNode* node, const char* tag)
 {
   return node && node->type == NODE_ELEMENT && 
   strcmp(node->tag, tag) == 0;
 }
 
 void extract_links(DOMNode* node)
 {
   if(!node)
      return;
      
  if(node->type == NODE_ELEMENT)
  {
    if(is_tag(node, "a"))
    {
      const char* href = get_attribute(node, "href");
      if(href)
        printf("LINK FOUND: %s\n", href);
    }
  }
  
  DOMNode* child = node->first_child;
  
  while(child)
  {
    extract_links(child);
    child = child->next_sibling;
  }
 }

