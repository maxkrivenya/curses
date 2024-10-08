#ifndef __framestack_h_
#define __framestack_h_

#include "frame.h"
#include "node-frame.h"

struct List* framestack_new();

void framestack_push_tail(
        struct List* framestack, 
        struct Frame* fr
);

void framestack_print(
        struct List* framestack, 
        struct Node* frame_ptr
);

void framestack_render(
        struct List* framestack, 
        struct Node* frame_ptr
);

void framestack_next(
        struct Node** frame_ptr, 
        struct Node** field_ptr
);

void framestack_pointers_init(
        struct List* framestack, 
        struct Node** frame_ptr, 
        struct Node** field_ptr
);

#endif
