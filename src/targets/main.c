#include "./../headers/framestack.h"

void do_stuff(struct Frame* fr, void* params){
    fr->bc = BACK_BLACK;
    fr->fc = FORE_RED;
}


int main(int argc, char* argv[]){
//FILE* mstream = fopen("mstream.txt", "w");
    int     cursor          = 0;
    char    input           = '\0';
    char    prev_input      = '\0';
    char*   screen_value    = (char*)calloc(WORDLEN_MAX, sizeof(char));

    struct List*    framestack  = list_new();
    struct Node*    frame_ptr;
    struct Node*    field_ptr;
    struct Node*    event_ptr;
    struct WinSize  pos         = {0, 0};
    
    framestack_push_tail(framestack, frame_console_new_default());
    framestack_push_tail(framestack, frame_new_from_file("./frames/auth.fr"));
    framestack_push_tail(framestack, frame_new_from_file("./frames/fio.fr"));

    frame_ptr = framestack->head->next;
    field_ptr = node_frame_get_first_field_node(frame_ptr);

    framestack_render(framestack, framestack->head->next);
    framestack_print(framestack, framestack->head->next);

    /*----------------input*----------------------*/

    /*---------------test---------------------*/
    struct Action* act = action_new(
                       '1', 
                       do_stuff, 
                       frame_ptr->value
    );
    node_frame_push_event(framestack->tail, act);
    /*---------------test---------------------*/
    do{
        do{
            pos     = node_frame_cursor_get(frame_ptr, field_ptr);

            node_frame_set_is_focus(field_ptr, 1);
            framestack_print(framestack, frame_ptr);
            frame_cursor_set(pos, cursor);

            prev_input = input;
            input = getchar();

            frame_cursor_set(pos, cursor);

            if(prev_input != SPEC_KEY){
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
                    case SPEC_KEY:{
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
                act = node_frame_get_action(field_ptr, input);
                if(act == NULL){ act = node_frame_get_action(frame_ptr, input);}
                if(act != NULL){ 
                    act->action(act->parent, act->parameters);
                }
            }
        }while(input != 'q' && cursor < ((struct Frame*)(field_ptr->value))->ws.width - 1);
        if(prev_input != SPEC_KEY){
            if(input == 'q'){
                break;
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



