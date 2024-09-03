#include "headers/framestack.h"

int main(int argc, char* argv[]){
    #ifdef linux
    if(argc > 1){
        char c = getopt(argc, argv, "rh");
        switch(c) {
            case 'r':{ rain(); return 0;}
            case 'h':{ hacker_screen(); return 0;}
            default:{printf("%s%sERROR: UNKNOWN OPT\n%s", BACK_BLACK, FORE_RED, RESET); return 1;}
        }
    }
    #endif
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
    struct Node* field_ptr = frame_get_first_field_node(((struct Frame*)(frame_ptr->value))->fields);
    struct WinSize pos = {0, 0};

    do{
        pos = cursor_get((struct Frame*)(frame_ptr->value), ((struct Frame*)(field_ptr->value)));
        ((struct Frame*)(field_ptr->value))->details.is_focus = 1;
        //frame_print((struct Frame*)(frame_ptr->value));
        framestack_print(framestack, frame_ptr);
        printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        do{
            input = getchar();
            printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        }while (input == '\0' || input == '\n');
        cursor++;
        if(input == '+'){   //going to be a switch case on frame_ptr->value->events
            //ring_next(((struct Frame*)(framestack->head->value))->fields);
            if(frame_ptr->next == NULL){
                frame_ptr = frame_ptr->prev;
            }else{
                frame_ptr = frame_ptr->next;

            }
                field_ptr = frame_get_first_field_node(((struct Frame*)(frame_ptr->value))->fields);
        }
        else{
            if(input != '\t'){
                *(((struct Frame*)(field_ptr->value))->buf + cursor*CHUNK) = input;
            }
            else{
                cursor = 0;
                input = '\0';
                ((struct Frame*)(field_ptr->value))->details.is_focus = 0;
                ring_next(((struct Frame*)(frame_ptr->value))->fields);
                field_ptr = ((struct Frame*)(frame_ptr->value))->fields->head;
                ((struct Frame*)(field_ptr->value))->details.is_focus = 1;
                pos = cursor_get((struct Frame*)(frame_ptr->value), ((struct Frame*)(field_ptr->value)));
                printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
            }
        }
    }while(input != 'q' && cursor < ((struct Frame*)(field_ptr->value))->ws.width - 1);

    list_free(framestack);

    printf(RESET);
    printf("\n\n");
    return 0;
}



