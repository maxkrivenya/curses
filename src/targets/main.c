#include "./../headers/framestack.h"

void node_frame_write(struct Node* node, int pos, char val){
    return frame_write((struct Frame*)(node->value), pos, val);
}

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


    FILE* mstream = fopen("mstream.txt", "w");
    /*----------------input*----------------------*/
    char input = '\0';
    int cursor = 0;
    struct Node* frame_ptr = framestack->head->next;
    struct Node* field_ptr = frame_get_first_field_node(
            ((struct Frame*)(frame_ptr->value))
            ->fields
    );
    struct WinSize pos = {0, 0};

    do{
        pos = cursor_get(
                (struct Frame*)(frame_ptr->value), 
                (struct Frame*)(field_ptr->value)
        );

        ((struct Frame*)(field_ptr->value))->details.is_focus = 1;
        framestack_print(framestack, frame_ptr);
        cursor_set(pos, cursor);

        do{
            input = getchar();
            cursor_set(pos, cursor);
        }while (input == '\0' || input == '\n');
        cursor++;

        if(input == '+'){   //going to be a switch case on frame_ptr->value->events
            input = '\0';
            cursor = 0;
            framestack_next(&frame_ptr, &field_ptr);
        }
        else{
            if(input != '\t' && input != '\n' && input != '\0'){
                node_frame_write(field_ptr, cursor, input);
            }
            else{
                input = '\0';
                cursor = 0;
                frame_next_field(&frame_ptr, &field_ptr, &pos);
            }
        }
    }while(input != 'q' && cursor < ((struct Frame*)(field_ptr->value))->ws.width - 1);

    list_free(framestack);

    printf(RESET);
    printf("\n\n");
    fclose(mstream);
    return 0;
}



