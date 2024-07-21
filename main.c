#include "fun_ctions.h"


int main(){

    struct Frame* console;
    console = new_console_full(BACK_BLUE, FORE_CYAN, "helo world!");

    struct WinSize ws1 = {22, 80};
    struct WinSize ws2 = {10, 50};
    struct Frame* fr20 =  new_frame(ws2, 0, 0, BACK_BLUE, FORE_CYAN, "Auth");
    struct Frame* frame21 = new_frame(get_winsize(1,15),   3, 10,  BACK_BLACK, FORE_YELLOW, "Login:   ");
    struct Frame* frame22 = new_frame(get_winsize(1,15),   7, 10,  BACK_BLACK, FORE_YELLOW, "Password:");
    push_frame(fr20, frame21);
    push_frame(fr20, frame22);
    

    struct Frame* fr =  new_frame(ws1, 0, 0, BACK_BLUE, FORE_CYAN, "what");
    struct Frame* frame1 = new_frame(get_winsize(1,20),   5, 10,  BACK_BLACK, FORE_YELLOW,  "Name:   ");
    struct Frame* frame2 = new_frame(get_winsize(1,20),   10, 10,  BACK_BLACK, FORE_YELLOW, "Surname:");
    struct Frame* frame3 = new_frame(get_winsize(1,20),   15, 10, BACK_BLACK, FORE_YELLOW, "Text:   ");

    push_frame(fr, frame1);
    push_frame(fr, frame2);
    push_frame(fr, frame3);

    push_frame(console, fr);
    push_frame(console, fr20);

    
    /*----------------input*----------------------*/
    char input = '\0';
    int cursor = 0;
    struct Node* nptr = get_first_field(console->field);
    struct WinSize pos = {0, 0};

    do{
        pos = get_cursor(console, nptr->fr);
        nptr->fr->is_focus = 1;
        print_frame(console);
        printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        do{
            input = getc(stdin);
            printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
        }while (input == '\0' || input == '\n');
        cursor++;
        if(input == '+'){
            pop(console->field /*, fr */);
            nptr = get_first_field(console->field);
        }
        else{
            if(input != '\t'){
                *(nptr->fr->buf + cursor*CHUNK) = input;
            }
            else{
                cursor = 0;
                input = '\0';
                nptr->fr->is_focus = 0;
                if(nptr->next != NULL){
                    nptr = nptr->next;
                }else{
                    do{
                        nptr = nptr->prev;
                    }while(nptr->prev != NULL);
                }
                nptr->fr->is_focus = 1;
                pos = get_cursor(console, nptr->fr);
                printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + cursor);
            }
        }
    }while(input != 'q' && cursor < nptr->fr->ws.width - 1);

    delete_frame(&console);

    printf(RESET);
    printf("\n\n");
    return 0;
}



