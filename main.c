#include "fun_ctions.h"
#include <ctype.h>


int main(){

    struct Frame* console;
    console = new_console_full(BACK_BLUE, FORE_CYAN, "helo world!");

    struct WinSize ws1 = {20, 40};
    struct WinSize ws1row = {1, 8};
    struct WinSize ws1row2 = {1, 20};

    struct Node* node   = get_node( new_frame(ws1row, 1, 10, BACK_BLACK, FORE_YELLOW, "TY PIDOR"), NULL, NULL);
    struct Node* node1  = get_node( new_frame(ws1row2, 5, 60, BACK_BLACK, FORE_YELLOW, "TY PIDOR"),  NULL, NULL);
    struct Node* node2  = get_node( new_frame(ws1, 10, 110, BACK_BLACK, FORE_YELLOW, "TY PIDOR"),   NULL, NULL);
    struct Frame* fr =  new_frame(ws1, 0, 0, BACK_BLACK, FORE_YELLOW, "TY PIDOR");

    push(console->field, node);
    push(console->field, node1);
    //push(console->field, node2);

    char input = '\0';
    int cursor = 0;
    struct Node* nptr = console->field->head;
    nptr->fr->is_focus = 1;
    do{
        print_frame(console);
        print_frame(console);
        do{
            input = getc(stdin);
        }while (!isalnum(input) && input != ' ');
        *(nptr->fr->buf + cursor*CHUNK) = input;
        cursor++;
    }while(input != 'q' && cursor < nptr->fr->ws.width - 1);


    delete_frame(&console);

    printf(RESET);
    printf("\n\n");
    return 0;
}



