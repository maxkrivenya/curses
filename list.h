#include "node.h"

struct List{
    struct Node* head;
    struct Node* tail;
};

struct List*    list_new();
void            list_push(struct List* list, struct Node* new_node);
struct Node*    list_pop(struct List* list);
void            list_free(struct List* list);

struct Ring{
    struct Node* head;
};

struct Ring*    ring_new();
void            ring_push(struct Ring* ring, struct Node* new_node);
struct Node*    ring_pop(struct Ring* ring);
void            ring_next(struct Ring* ring);
void            ring_free(struct Ring* ring);
void ring_print(struct Ring* ring);
