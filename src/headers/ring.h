#ifndef __ring_h_
#define __ring_h_
#include "node.h"

struct Ring{
    struct Node* head;
};

struct Ring*    ring_new();
void            ring_push(struct Ring* ring, struct Node* new_node);
struct Node*    ring_pop(struct Ring* ring);
void            ring_next(struct Ring* ring);
void            ring_free(struct Ring* ring);
void ring_print(struct Ring* ring);

#endif
