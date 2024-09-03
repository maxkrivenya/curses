#include "./../headers/framestack.h"
//TODO: i should probably start reading strings and not chars....
//that way i have to call render && print once per input rather than every char

//TODO: add frame search in some_PATH

//TODO: make ON-EVENTS:
//  1. GOTO - search for a specified .fr file and push it onto framestack.
//  2. maybe something like SET arg1 arg2 -> switch call a frame_set func

//TODO: add buttons
//  a field with 'y' == 'q'?
//TODO: add checkboxes
//TODO: add radiosets ig

int main(int argc, char* argv[]){

    int     cursor          = 0;
    int     field_width     = 0;
    char    input           = '\0';
    char    prev_input      = '\0';
    char*   screen_value    = (char*)calloc(WORDLEN_MAX, sizeof(char));

    struct List*    framestack  = framestack_new();
    struct Node*    frame_ptr;
    struct Node*    field_ptr;
    struct Node*    event_ptr;
    struct WinSize  cursor_pos  = {0, 0};
    
    framestack_push_tail(framestack, frame_new_from_file("./frames/auth.fr"));
    framestack_push_tail(framestack, frame_new_from_file("./frames/fio.fr"));

    /* framestack_init */
    framestack_pointers_init(framestack, &frame_ptr, &field_ptr);
    framestack_render(framestack, frame_ptr);  
    framestack_print(framestack,  frame_ptr); 
    /* framestack_init */

    /*----------------input----------------------*/

    do{
        do{
            field_width = ((struct Frame*)(field_ptr->value))->ws.width - 1;
            
            cursor_pos = node_frame_cursor_get(frame_ptr, field_ptr);
            node_frame_set_is_focus(field_ptr, 1);

            framestack_print(framestack, frame_ptr);
            frame_cursor_set(cursor_pos, cursor);

            prev_input = input;
            input = getchar();

            if(prev_input != SPEC_KEY){
                switch(input){
                    case '+' :{
                                  node_frame_get_screen_value(field_ptr, screen_value);
                                  framestack_next(&frame_ptr, &field_ptr);

                                  cursor  = 0;
                                  break;
                              }
                    case '\t':{
                                  node_frame_get_screen_value(field_ptr, screen_value);
                                  frame_next_field(&frame_ptr, &field_ptr, &cursor_pos);

                                  cursor  = 0;
                                  break;
                              }
                    case '\n':{
                                  break;
                              }
                    default:{
                                node_frame_write(field_ptr, cursor, input);
                                node_frame_get_screen_value(field_ptr, screen_value);
                                cursor++;
                                break;
                            }
                }
            }else{
                node_frame_handle_action(frame_ptr, field_ptr, input);
            }
        }while(input != 'q' && cursor < field_width);
        if(prev_input != SPEC_KEY){
            if(input == 'q'){
                list_pop_tail(framestack);
                framestack_pointers_init(framestack, &frame_ptr, &field_ptr);
                if(frame_ptr == NULL){
                    break;
                }
            }else{
                //TODO: make an alert-box
                //1. push a frame with text and a button to framestack
                //2. wait-for 'q' 
                //3. pop
            }
        }
    }while(1);

    list_free(framestack);
    free(screen_value);

    printf(RESET);
    printf("\n\n");
    return 0;
}



