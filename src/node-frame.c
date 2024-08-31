#include "./headers/node-frame.h"
#include "headers/frame.h"

void node_frame_write(struct Node* node, int pos, char val){
    return frame_write((struct Frame*)(node->value), pos, val);
}

struct Node* node_frame_get_first_field_node(struct Node* node){
    return frame_get_first_field_node( ((struct Frame*)(node->value))->fields );
}

struct WinSize node_frame_cursor_get(struct Node* fr, struct Node* x){
    return frame_cursor_get(
            ((struct Frame*)(fr->value)),
            ((struct Frame*)(x->value))
    );
}

void* node_frame_handle_action(struct Node* frame_ptr, struct Node* field_ptr, char trigger){
    return frame_handle_action(
            ((struct Frame*)(frame_ptr->value)),
            ((struct Frame*)(field_ptr->value)),
            trigger);
}

void node_frame_set_is_focus(struct Node* node, int val){
    return frame_set_is_focus((struct Frame*)(node->value), val);
}

void node_frame_set_bc(struct Node* node, const char* bc){
    return frame_set_bc((struct Frame*)(node->value), bc);
}

void node_frame_set_fc(struct Node* node, const char* fc){
    return frame_set_fc((struct Frame*)(node->value), fc);
}

void node_frame_get_screen_value(struct Node* node, char* dest){
    return frame_get_screen_value((struct Frame*)(node->value), dest);
}

struct Action* node_frame_get_action(struct Node* node, char trigger){
    return frame_get_action(((struct Frame*)(node->value)), trigger);
}

void node_frame_push_event(struct Node* node, struct Action* act){
    frame_push_event((struct Frame*)(node->value), act);
}
