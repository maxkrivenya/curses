#include "fun_ctions.h"


int main(){

    struct Frame* console;
    console = new_console_full(BACK_BLUE, FORE_CYAN, "helo world!");

    struct WinSize ws1 = {20, 40};
    struct WinSize ws1row = {1, 8};
    struct WinSize ws1row2 = {1, 20};

    struct Frame* frame1row     = new_frame(ws1row,     BACK_BLACK, FORE_YELLOW, "TY PIDOR");
    struct Frame* frame1row2    = new_frame(ws1row2,    BACK_BLACK, FORE_YELLOW, "TY PIDOR");
    struct Frame* frame1        = new_frame(ws1,        BACK_BLACK, FORE_YELLOW, "TY PIDOR");
    struct Frame* frame2        = new_frame(ws1,        BACK_BLUE,  FORE_CYAN,   "field");

    struct Node* node   = get_node(frame2,      1,  10,     NULL, NULL);
    struct Node* node1  = get_node(frame2,      5,  60,     NULL, NULL);
    struct Node* node2  = get_node(frame2,      10, 110,    NULL, NULL);
    struct Node* node3  = get_node(frame2,      27, 60,     NULL, NULL);
    struct Node* node4  = get_node(frame2,      30, 10,     NULL, NULL);
    struct Node* node5  = get_node(frame1row,   1,  110,    NULL, NULL);
    struct Node* node6  = get_node(frame1row2,  4,  110,    NULL, NULL);

    push(console->field, node6);
    push(console->field, node);
    push(console->field, node1);
    push(console->field, node2);
    push(console->field, node3);
    push(console->field, node5);
    push(console->field, node4);

    print_frame(console);

    delete_frame(&console);
    delete_frame(&frame1);
    delete_frame(&frame2);

    printf(RESET);
    printf("\n\n");
    return 0;
}



