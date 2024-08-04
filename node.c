#ifndef __node_h_
#include "node.h"
#endif
#ifndef __frame_h_
#include "frame.h"
#endif

struct Node* node_new(void* value){
   struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));

   if(value == NULL){return node;}
   node->value = value;
   node->prev = NULL;
   node->next = NULL;

   return node;
}


void node_delete(struct Node* node){
    if(sizeof(*(node->value)) == sizeof(struct Frame)){
        frame_delete((struct Frame**)(&node->value));
    }
}
