#ifndef __node_frame_h_
#define __node_frame_h_
#include "action.h"
#include "frame.h"

void node_frame_write(struct Node* node, int pos, char val);
struct Node* node_frame_get_first_field_node(struct Node* node);
struct WinSize node_frame_cursor_get(struct Node* fr, struct Node* x);
void node_frame_set_is_focus(struct Node* node, int val);
void node_frame_get_screen_value(struct Node* node, char* dest);
void node_frame_set_bc(struct Node* node, const char* bc);
void node_frame_set_fc(struct Node* node, const char* fc);
void node_frame_push_event(struct Node* node, struct Action* act);

void* node_frame_handle_action(struct Node* frame_ptr, struct Node* field_ptr, char trigger);
struct Action* node_frame_get_action(struct Node* node, char trigger);
#endif
