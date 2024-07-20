#include "frame.h"

struct Node{
    struct Frame* fr;
    int row;
    int col;
    int is_focus;
    struct Node* prev;
    struct Node* next;
};

struct Node* get_node(struct Frame* fr,
                      int row,
                      int col,
                      struct Node* prev,
                      struct Node* next
);

void delete_node(struct Node* node);
