#ifndef __list_h_
#define __list_h_
#include "node.h"

struct List{
    struct Node* head;
    struct Node* tail;
};

struct List*    list_new();
void            list_push_tail(struct List* list, struct Node* new_node);
struct Node*    list_pop(struct List* list);
void            list_free(struct List* list);

#endif
