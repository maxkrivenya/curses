#include "fun_ctions.h"


int main(){

    struct Frame* console;
    console = new_console_full(BACK_BLUE, FORE_CYAN, "helo world!");

    struct WinSize ws1 = {20, 80};
    struct WinSize ws1row = {1, 8};
    struct WinSize ws1row2 = {1, 20};

    struct Node* node   = get_node( new_frame(ws1row,   1, 10,      BACK_BLACK, FORE_YELLOW, "TY PIDOR"), NULL, NULL);
    struct Node* node1  = get_node( new_frame(ws1row2,  5, 60,      BACK_BLACK, FORE_YELLOW, "TY PIDOR"),  NULL, NULL);
    struct Node* node2  = get_node( new_frame(ws1,      10, 110,    BACK_BLACK, FORE_YELLOW, "TY PIDOR"),   NULL, NULL);
    struct Frame* fr =  new_frame(ws1, 1, 1, BACK_BLACK, FORE_YELLOW, "TY PIDOR");

    push(console->field, node);
    push(console->field, node1);
    push(console->field, node2);

    char input = '\0';
    int cursor = 0;
    struct Node* nptr = console->field->head;
    //nptr->fr->is_focus = 1;
    do{
        nptr->fr->is_focus = 1;
        print_frame(console);
        printf("%s%s", BACK_CYAN, FORE_YELLOW);
        printf("\033[%d;%dH", nptr->fr->row + 1, nptr->fr->col + 1 + cursor);
        printf(RESET);
        printf("%s%s", nptr->fr->bc, nptr->fr->fc);
        do{
            input = getc(stdin);
        }while (input == '\0' || input == '\n');
        if(input != '\t'){
            *(nptr->fr->buf + cursor*CHUNK) = input;
            cursor++;
        }
        else{
            cursor = 0;
            input = '\0';
            nptr->fr->is_focus = 0;
            if(nptr->next != NULL){
                nptr = nptr->next;
            }else{
                nptr = console->field->head;
            }
            nptr->fr->is_focus = 1;
        }
    }while(input != 'q' && cursor < nptr->fr->ws.width - 1);

    /*
    *(fr->buf + CHUNK * 0) = 'P';
    *(fr->buf + CHUNK * 1) = 'I';
    *(fr->buf + CHUNK * 2) = 'D';
    *(fr->buf + CHUNK * 3) = 'O';
    *(fr->buf + CHUNK * 4) = 'R';
    running_frame(console, fr);
    */
    delete_frame(&console);

    printf(RESET);
    printf("\n\n");
    return 0;
}



