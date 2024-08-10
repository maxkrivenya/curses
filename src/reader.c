#include "./headers/framestack.h"
#include "./headers/book.h"
#include "headers/frame.h"
#include "headers/list.h"

int main(){
    struct Book* book = book_new("./src/frame.c");
    struct Frame* nav = frame_new_from_file("/home/myra/code_shenanigans/c/frame/frames/nav.fr");
    struct Node* nptr = book->index->head;
    struct List* framestack = list_new();
    framestack_push_tail(framestack, book->pages);
    while(nptr != NULL){
        printf("%lu\n", *(long*)nptr->value);
        nptr = nptr->next;
}
    char input = '\0';
    book_pages_load(book);
    //frame_print(book->pages);
    framestack_print(framestack, framestack->tail);
    do{

        framestack_print(framestack, framestack->tail);
        do{
            input = fgetc(stdin);
        }while(input == '\n');
        switch(input){
            case '+':{
                         book->pagenum++;
                         book_pages_load(book);
                         //frame_print(book->pages);
                         framestack_print(framestack, framestack->head);
                         break;
                     }
            case '-':{
                         book->pagenum--;
                         if(book->pagenum < 0) { book->pagenum = 0; } 
                         book_pages_load(book);
                         //frame_print(book->pages);
                         framestack_print(framestack, framestack->head);
                         break;
                     }
            case 'n':{
                         framestack_push_tail(framestack, nav);
                         framestack_print(framestack, framestack->tail);
                         sleep(2);
                         list_pop_tail(framestack);
                         framestack_render(framestack, framestack->head);
                         break;
                     }
            default:{
                        break;
                    }
        }
    }while(input != 'q');

    book_delete(&book);
    list_free(framestack);
    frame_delete(&nav);

    return 0;
}
