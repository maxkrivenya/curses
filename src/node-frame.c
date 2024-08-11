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

void node_frame_set_is_focus(struct Node* node, int val){
    return frame_set_is_focus((struct Frame*)(node->value), val);
}
void node_frame_get_screen_value(struct Node* node, char* dest){
    return frame_get_screen_value((struct Frame*)(node->value), dest);
}
