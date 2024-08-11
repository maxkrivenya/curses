#include "./headers/framestack.h"

void framestack_push_tail(struct List* framestack, struct Frame* fr){
    struct WinSize ws = get_console_size();
    if(!fr->row || !fr->col){
        fr->row = (ws.height - fr->ws.height) / 2;
        fr->row = fr->row - fr->row % CHUNK;
        fr->col = (ws.width - fr->ws.width) / 2;
        fr->col = fr->col - fr->col % CHUNK;
        fr->details.is_field = 0;
    }
    list_push_tail(framestack, node_new(fr));
}

void framestack_print(struct List* framestack, struct Node* frame_ptr){
    //ik this is kinda ass but i really dont want to deal with this rn
    struct Frame* console = (struct Frame*)framestack->head->value;
    console->fields->head = frame_ptr;
    frame_print(console);
    console->fields->head = NULL;
    return;
}

void framestack_render(struct List* framestack, struct Node* frame_ptr){
    if(frame_ptr == framestack->head){ return; }
    struct Frame* console = (struct Frame*)framestack->head->value;
    frame_clear(console);
    struct Node* nptr = framestack->head->next;
    while(nptr != frame_ptr){
        render_frame_to_frame(console, (struct Frame*)nptr->value, 2);
        nptr = nptr->next;
    }
    printf(RESET);
}

void framestack_next(struct Node** frame_ptr, struct Node** field_ptr){
    if((*frame_ptr)->next == NULL){
        *frame_ptr = (*frame_ptr)->prev;
    }else{
        *frame_ptr = (*frame_ptr)->next;
    }
    *field_ptr = frame_get_first_field_node(((struct Frame*)((*frame_ptr)->value))->fields);
}

