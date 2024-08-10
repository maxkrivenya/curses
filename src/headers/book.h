#ifndef __book_h_
#define __book_h_
#include "./frame.h"

struct Book{
    char* filename;
    char* buffer;
    FILE* fptr;
    int   pagenum;
    struct Frame* pages;
    struct List*  index; 
};
struct Book* book_new(char* filename);
void book_init_index(struct Book* book);
long book_get_page_offset(struct Book* book);
void book_pages_load(struct Book* book);
void book_delete(struct Book** book);
void book_print_pagenum(struct Book* book);
#endif
