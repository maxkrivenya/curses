#include "./headers/frame.h"

struct List* framestack;

int main(int argc, char* argv[]){
    if(argc > 1){
        char c = getopt(argc, argv, "rh");
        switch(c) {
            case 'r':{ rain(); return 0;}
            case 'h':{ hacker_screen(); return 0;}
            default:{printf("%s%sERROR: UNKNOWN OPT\n%s", BACK_BLACK, FORE_RED, RESET); return 1;}
        }
    }

    list_push_tail(framestack, node_new(frame_console_new_default()));
    struct Frame* console;
    console = frame_console_new(BACK_BLUE, FORE_CYAN, "helo world!");

    struct Frame* fr20      = frame_new_from_file("./frames/auth.fr");
    struct Frame* fr        = frame_new_from_file("./frames/fio.fr");

    frame_push_field(console, fr);
    frame_push_field(console, fr20);

    /*----------------input*----------------------*/
    char input = '\0';
    int cursor = 0;
    struct Node* nptr = frame_get_first_field_node(console->fields);
    struct WinSize pos = {0, 0};

    do{
        pos = cursor_get(console, ((struct Frame*)(nptr->value)));
        ((struct Frame*)(nptr->value))->details.is_focus = 1;
        frame_print(console);
        printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        do{
            input = getchar();
            printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        }while (input == '\0' || input == '\n');
        cursor++;
        if(input == '+'){
            ring_next(console->fields);
            nptr = frame_get_first_field_node(console->fields);
        }
        else{
            if(input != '\t'){
                *(((struct Frame*)(nptr->value))->buf + cursor*CHUNK) = input;
            }
            else{
                cursor = 0;
                input = '\0';
                ((struct Frame*)(nptr->value))->details.is_focus = 0;
                if(nptr->next != NULL){
                    nptr = nptr->next;
                }else{
                    do{
                        nptr = nptr->prev;
                    }while(nptr->prev != NULL);
                }
                ((struct Frame*)(nptr->value))->details.is_focus = 1;
                pos = cursor_get(console, ((struct Frame*)(nptr->value)));
                printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
            }
        }
    }while(input != 'q' && cursor < ((struct Frame*)(nptr->value))->ws.width - 1);

    list_free(framestack);
    frame_delete(&console);

    printf(RESET);
    printf("\n\n");
    return 0;
}



