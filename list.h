#include "node.h"

struct List{
    struct Node* head;
    struct Node* tail;
};

struct List* new_list();

void push_field(struct List* list, struct Node* new_node);
void pop(struct List* list);

void free_list(struct List* list);
