#include "./headers/framestack.h"
#include "./headers/book.h"

int main(){
    struct Book* book = book_new("./src/main.c");
    book_pages_load(book);
    frame_print(book->pages);
    book_delete(&book);
    return 0;
}
