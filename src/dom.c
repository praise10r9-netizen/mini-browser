#include "../include/dom.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DOMNode *create_element(const char* tag)
{
  DOMNode* node = malloc(sizeof(DOMNode));
  if(!node)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  node->type = NODE_ELEMENT;
  
  snprintf(node->tag, sizeof(node->tag), "%s", tag);
  node->text[0] = '\0';
  
  node->attributes = NULL;
  
  node->parent = NULL;
  node->first_child = NULL;
  node->next_sibling = NULL;
  
  return node;
}

DOMNode *create_text(const char* text)
{
  DOMNode *node = malloc(sizeof(DOMNode));
  if(!node)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  node->type = NODE_TEXT;
  
  snprintf(node->text, sizeof(node->text), "%s", text);
  node->tag[0] = '\0';
  node->attributes = NULL;
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

void add_attribute(DOMNode* node, const char* name, const char* value)
{
  DOMAttr* attr = malloc(sizeof(DOMAttr));
  if(!attr)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  snprintf(attr->name,sizeof(attr->name),"%s",name);
  snprintf(attr->value,sizeof(attr->value),"%s",value);
  
  attr->next = node->attributes;
  node->attributes = attr;
}

const char* get_attribute(DOMNode* node,const char* name)
{
  DOMAttr* attr = node->attributes;
  while(attr)
  {
    if(strcmp(attr->name,name)==0)
       return attr->value;
       
    attr = attr->next;
  }
  return NULL;
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
    print_dom(child, depth+1);
    child = child->next_sibling;
  }
}
