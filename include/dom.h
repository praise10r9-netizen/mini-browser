#ifndef DOM_H
#define DOM_H

typedef enum
{
  NODE_ELEMENT,
  NODE_TEXT
}NodeType;

typedef struct DOMNode
{
  NodeType type;
  char tag[64];
  char text[256];
  
  struct DOMNode* parent;
  struct DOMNode* first_child;
  struct DOMNode* next_sibling;
  
}DOMNode;

DOMNode* create_element(const char* tag);
DOMNode* create_text(const char* text);
void append_child(DOMNode *parent, DOMNode *child);
void print_dom(DOMNode* node, int depth);
#endif
