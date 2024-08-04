#ifndef __node_h_
#define __node_h_
#include "defines.h"

struct Node{
    struct Frame* fr;
    struct Node* prev;
    struct Node* next;
};

struct Node* node_new(struct Frame* fr);

void node_delete(struct Node* node);
#endif
