#ifndef __node_h_
#define __node_h_
#include "defines.h"

struct Node{
    //struct Frame* fr;
    void* value;
    struct Node* prev;
    struct Node* next;
};

struct Node* node_new(void* val);

void node_delete(struct Node* node);
#endif
