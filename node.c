#include "node.h"

struct Node* get_node(struct Frame* fr,
        int row,
        int col,
        struct Node* prev,
        struct Node* next
){
   struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));
   node->next = next;
   node->prev = prev;

   node->row = row;
   node->col = col;
   node->is_focus = 0;

   if(fr == NULL){return node;}
   node->fr = fr;

   return node;
}


void delete_node(struct Node* node){
    delete_frame(&node->fr);
}
