#ifndef DOM_H
#define DOM_H

typedef enum
{
  NODE_ELEMENT,
  NODE_TEXT
}NodeType;

typedef struct DOMAttr
{
  char name[64];
  char value[256];
  struct DOMAttr* next;
}DOMAttr;

typedef struct DOMNode
{
  NodeType type;
  char tag[64];
  char text[256];
  
  DOMAttr* attributes;
  
  struct DOMNode* parent;
  struct DOMNode* first_child;
  struct DOMNode* next_sibling;
  
}DOMNode;

DOMNode* create_element(const char* tag);
DOMNode* create_text(const char* text);
void append_child(DOMNode *parent, DOMNode *child);
void add_attribute(DOMNode *node, const char* name,const char* value);
const char *get_attribute(DOMNode* node,const char* name);
void print_dom(DOMNode* node, int depth);

#endif
