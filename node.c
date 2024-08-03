#include "node.h"

struct Node* node_new(struct Frame* fr){
   struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));

   if(fr == NULL){return node;}
   node->fr = fr;
   node->prev = NULL;
   node->next = NULL;

   return node;
}


void node_delete(struct Node* node){
    frame_delete(&node->fr);
}
