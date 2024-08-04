#include "frame.h"


struct Frame* frame_first;
struct Node*  node_frame_current;


int main(int argc, char* argv[]){
    if(argc > 1){
        char c = getopt(argc, argv, "rh");
        switch(c) {
            case 'r':{ rain(); return 0;}
            case 'h':{ hacker_screen(); return 0;}
            default:{printf("%s%sERROR: UNKNOWN OPT\n%s", BACK_BLACK, FORE_RED, RESET); return 1;}
        }
    }

    struct Frame* console;
    console = frame_console_new(BACK_BLUE, FORE_CYAN, "helo world!");
    frame_first     = console;

    struct Frame* fr20      = frame_new_from_file("./auth.fr");
    struct Frame* fr        = frame_new_from_file("./fio.fr");

    frame_field_push(console, fr);
    frame_field_push(console, fr20);

    if(frame_first == NULL){
        ERROR("FRAME_FIRST = NULL");
        exit(-1);
    }
    if(frame_first->frames != NULL){
        if(frame_first->frames->head != NULL){
            node_frame_current   = frame_first->frames->head;
        }else{
            ERROR("bad fields!");
        }
    }else{
        ERROR("no fields!");
    }
    /*----------------input*----------------------*/
    char input = '\0';
    int cursor = 0;
    struct Node* nptr = frame_get_first_field_node(console->field);
    struct WinSize pos = {0, 0};

    do{
        pos = cursor_get(console, nptr->fr);
        nptr->fr->details.is_focus = 1;
        frame_print(console);
        printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        do{
            input = getchar();
            printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        }while (input == '\0' || input == '\n');
        cursor++;
        if(input == '+'){
            ring_next(console->field);
            nptr = frame_get_first_field_node(console->field);
        }
        else{
            if(input != '\t'){
                *(nptr->fr->buf + cursor*CHUNK) = input;
            }
            else{
                cursor = 0;
                input = '\0';
                nptr->fr->details.is_focus = 0;
                if(nptr->next != NULL){
                    nptr = nptr->next;
                }else{
                    do{
                        nptr = nptr->prev;
                    }while(nptr->prev != NULL);
                }
                nptr->fr->details.is_focus = 1;
                pos = cursor_get(console, nptr->fr);
                printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
            }
        }
    }while(input != 'q' && cursor < nptr->fr->ws.width - 1);

    frame_delete(&console);

    printf(RESET);
    printf("\n\n");
    return 0;
}



