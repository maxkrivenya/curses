#ifndef __node_frame_h_
#define __node_frame_h_
#include "frame.h"

void node_frame_write(struct Node* node, int pos, char val);
struct Node* node_frame_get_first_field_node(struct Node* node);
struct WinSize node_frame_cursor_get(struct Node* fr, struct Node* x);
void node_frame_set_is_focus(struct Node* node, int val);
void node_frame_get_screen_value(struct Node* node, char* dest);
#endif
