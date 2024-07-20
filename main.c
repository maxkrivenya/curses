#include "fun_ctions.h"


int main(){

    struct Frame* console;
    console = new_console_full(BACK_BLUE, FORE_CYAN, "helo world!");

    struct WinSize ws1 = {20, 40};
    struct WinSize ws1row = {1, 8};
    struct WinSize ws1row2 = {1, 20};

    struct Node* node   = get_node( new_frame(ws1row, 1, 10, BACK_BLACK, FORE_YELLOW, "TY PIDOR"), NULL, NULL);
    struct Node* node1  = get_node( new_frame(ws1row2, 5, 60, BACK_BLACK, FORE_YELLOW, "TY PIDOR"),  NULL, NULL);
    struct Node* node2  = get_node( new_frame(ws1, 10, 110, BACK_BLACK, FORE_YELLOW, "TY PIDOR"),   NULL, NULL);

    push(console->field, node);
    push(console->field, node1);
    push(console->field, node2);

    print_frame(console);

    delete_frame(&console);

    printf(RESET);
    printf("\n\n");
    return 0;
}



