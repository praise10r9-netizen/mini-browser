#include "../include/dom.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DOMNode *create_element(const char* tag)
{
  DOMNode* node = malloc(sizeof(DOMNode));
  
  node->type = NODE_ELEMENT;
  strncpy(node->tag, tag,sizeof(node->tag));
  node->text[0] = 0;
  
  node->parent = NULL;
  node->first_child = NULL;
  node->next_sibling = NULL;
  
  return node;
}

DOMNode *create_text(const char* text)
{
  DOMNode *node = malloc(sizeof(DOMNode));
  node->type = NODE_TEXT;
  strncpy(node->next, text, sizeof(node->text));
  node->tag[0] = 0;
  
  node->parent = NULL;
  node->first_child = NULL;
  node->next_sibling = NULL;
  
  return node;
}

void append_child(DOMNode* parent, DOMNode* child)
{
 child->parent = parent;
 if(!parent->first_child)
 {
   parent->first_child = child;
   return;
 }
 
 DOMNode *sibling = parent->first_child;
 
 while(sibling->next_sibling)
 	sibling = sibling->next_sibling;
 	
 sibling->next_sibling = child;
}

void print_dom(DOMNode* node, int depth)
{
  for(int i = 0; i<depth; i++)
     printf(" ");
     
  if(node->type == NODE_ELEMENT)
     printf("<%s>\n", node->tag);
  else
     printf("\"%s\"\n", node->text);
     
  DOMNode* child = node->first_child;
  
  while(child)
  {
    print(child, depth+1);
    child = child->next_sibling;
  }
}
