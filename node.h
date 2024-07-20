#include "frame.h"

struct Node{
    struct Frame* fr;
    struct Node* prev;
    struct Node* next;
};

struct Node* get_node(struct Frame* fr,
                      struct Node* prev,
                      struct Node* next
);

void delete_node(struct Node* node);
