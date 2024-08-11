#include "./../headers/framestack.h"

int main(int argc, char* argv[]){

    int     cursor          = 0;
    char    input           = '\0';
    char*   screen_value    = (char*)calloc(WORDLEN_MAX, sizeof(char));

    struct List*    framestack  = list_new();
    struct Node*    frame_ptr;
    struct Node*    field_ptr;
    struct WinSize  pos         = {0, 0};
    
    framestack_push_tail(framestack, frame_console_new_default());
    framestack_push_tail(framestack, frame_new_from_file("./frames/auth.fr"));
    framestack_push_tail(framestack, frame_new_from_file("./frames/fio.fr"));
    
    frame_ptr = framestack->head->next;
    field_ptr = node_frame_get_first_field_node(frame_ptr);

    framestack_render(framestack, framestack->head->next);
    framestack_print(framestack, framestack->head->next);

    /*----------------input*----------------------*/

    do{
        input   = '\0';
        pos     = node_frame_cursor_get(frame_ptr, field_ptr);

        node_frame_set_is_focus(field_ptr, 1);
        framestack_print(framestack, frame_ptr);
        frame_cursor_set(pos, cursor);

        input = getchar();
        frame_cursor_set(pos, cursor);

        switch(input){
            case '+' :{   //going to be a switch case on frame_ptr->value->events
                          node_frame_get_screen_value(field_ptr, screen_value);
                          framestack_next(&frame_ptr, &field_ptr);

                          cursor  = 0;
                          break;
                      }
            case '\t':{
                          node_frame_get_screen_value(field_ptr, screen_value);
                          frame_next_field(&frame_ptr, &field_ptr, &pos);

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
    }while(input != 'q' && cursor < ((struct Frame*)(field_ptr->value))->ws.width - 1);

    list_free(framestack);
    free(screen_value);

    printf(RESET);
    printf("\n\n");
    return 0;
}



