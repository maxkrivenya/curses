#include "./../headers/framestack.h"

int main(){
    struct List* framestack = list_new();
    framestack_push_tail(framestack, frame_console_new_no_name(BACK_BLACK, FORE_YELLOW));
    struct Frame* card = frame_new_from_file("./frames/card.fr");
    *(card->buf + card->ws.width*CHUNK + CHUNK) = '6';
    *(card->buf + card->ws.width*CHUNK + CHUNK + 1) = '\0';
    *(card->buf + card->ws.width*CHUNK + CHUNK + 2) = '\0';
    *(card->buf + card->ws.width*CHUNK + CHUNK + 3) = '\0';
    *(card->buf + card->ws.width*CHUNK + 2*CHUNK) = '<';
    *(card->buf + card->ws.width*CHUNK + 2*CHUNK + 1) = '\0';
    *(card->buf + card->ws.width*CHUNK + 2*CHUNK + 2) = '\0';
    *(card->buf + card->ws.width*CHUNK + 2*CHUNK + 3) = '\0';
    *(card->buf + card->ws.width*CHUNK + 3*CHUNK) = '>';
    *(card->buf + card->ws.width*CHUNK + 3*CHUNK + 1) = '\0';
    *(card->buf + card->ws.width*CHUNK + 3*CHUNK + 2) = '\0';
    *(card->buf + card->ws.width*CHUNK + 3*CHUNK + 3) = '\0';
    framestack_push_tail(framestack, card);
    framestack_print(framestack, framestack->tail);
    list_free(framestack);
    return 0;
}
