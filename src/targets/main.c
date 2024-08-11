#include "./../headers/framestack.h"

int main(int argc, char* argv[]){
    if(argc > 1){
        char c = getopt(argc, argv, "rh");
        switch(c) {
            case 'r':{ rain(); return 0;}
            case 'h':{ hacker_screen(); return 0;}
            default:{
                        printf("%s%sERROR: UNKNOWN OPT\n%s", BACK_BLACK, FORE_RED, RESET); 
                        return 1;
                    }
        }
    }
    struct List* framestack = list_new();
    
    framestack_push_tail(framestack, frame_console_new_default());
    framestack_push_tail(framestack, frame_new_from_file("./frames/auth.fr"));
    framestack_push_tail(framestack, frame_new_from_file("./frames/fio.fr"));
    
    framestack_render(framestack, framestack->head->next);
    framestack_print(framestack, framestack->head->next);

    /*----------------input*----------------------*/
    char input = '\0';
    int cursor = 0;
    struct Node* frame_ptr = framestack->head->next;
    struct Node* field_ptr = node_frame_get_first_field_node(frame_ptr);
    struct WinSize pos = {0, 0};

    do{
        pos = node_frame_cursor_get(frame_ptr, field_ptr);
        node_frame_set_is_focus(field_ptr, 1);

        framestack_print(framestack, frame_ptr);
        frame_cursor_set(pos, cursor);

        do{
            input = getchar();
            frame_cursor_set(pos, cursor);
        }while (input == '\0' || input == '\n');
        cursor++;

        if(input == '+'){   //going to be a switch case on frame_ptr->value->events
            framestack_next(&frame_ptr, &field_ptr);
        }
        else{
            if(input != '\t' && input != '\n' && input != '\0'){
                node_frame_write(field_ptr, cursor, input);
            }
            else{
                frame_next_field(&frame_ptr, &field_ptr, &pos);
            }
        }
        input = '\0';
        cursor = 0;
    }while(input != 'q' && cursor < ((struct Frame*)(field_ptr->value))->ws.width - 1);

    list_free(framestack);

    printf(RESET);
    printf("\n\n");
    return 0;
}



