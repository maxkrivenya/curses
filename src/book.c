#include "./headers/book.h"
#include "headers/defines.h"
#include "headers/frame.h"

struct Book* book_new(char* filename){
    FILE* fptr = fopen(filename, "r");
    if(fptr == NULL){
        return NULL;
    }
    struct Book* book = (struct Book*)calloc(1, sizeof(struct Book));
    book->pages     = frame_console_new(BACK_BLACK, FORE_CYAN, filename);
    book->buffer    = (char*)calloc(book->pages->ws.width * book->pages->ws.height * CHUNK, sizeof(char));
    book->filename  = (char*)calloc(STRLEN_MAX, sizeof(char));
    book->fptr      = fptr;
    book->index     = list_new();
    book->pagenum   = 0;
    book_init_index(book);
    return book;
}

void book_init_index(struct Book* book){
    FILE* fptr = book->fptr;
    if(fptr == NULL){ ERROR("COULDNT OPEN FILE"); return ; }
    long pos    = 0;    //file offset
    int amt    = 0;    //amt of rows
    int strlen  = 0;    //len of current row
    int row_width = (book->pages->ws.width) / 2 - 4;
    int row_amt   = book->pages->ws.height  - 4;
    char c;

    do{
        c = fgetc(fptr);
        pos++;
        strlen++;
        if(c == '\n' || c == '\0' || strlen == row_width){
            amt++;
            strlen = 0;
        }
        if(amt == 2*row_amt){
            long* val = (long*)calloc(1, sizeof(long));
            *val = pos;
            list_push_tail(book->index, node_new((void*)val));

            pos = 0;
            amt = 0;
        }
    }while(!feof(fptr));

}

long book_get_page_offset(struct Book* book){
    long offset = 0;
    struct Node* nptr = book->index->head;
    for(int i = 0; i < book->pagenum; i++){
        if(nptr != NULL){
            offset += *(long*)(nptr->value);
            nptr = nptr->next;
        }
    }
    return offset;
}

void book_pages_load(struct Book* book){
    if(book == NULL){ return; }
    if(book->fptr == NULL){ return; }
    if(book->buffer == NULL){ return; }
    if(book->filename == NULL){ return; }
    frame_clear(book->pages);

    int row_width = (book->pages->ws.width) / 2 - 4;
    int row_amt   = book->pages->ws.height  - 4;
    char* str = (char*)calloc(row_width + 1, sizeof(char));
    if(str == NULL){ return; }
    char* pos = NULL;
    pos = book->pages->buf;
    for(int i = 1; i < book->pages->ws.height - 1; i++){
        pos += book->pages->ws.width * CHUNK;
        sprintf(pos + (row_width - 1)*CHUNK, WALL);
        sprintf(pos + (row_width)*CHUNK, WALL);
    }

    fseek(book->fptr, book_get_page_offset(book), SEEK_SET);
    pos = book->pages->buf + (book->pages->ws.width + 1) * CHUNK; 
    for(int i = 0; i < row_amt; i++){
        if(feof(book->fptr)){ break; }
        fgets(str, row_width, book->fptr);
        if(str == NULL){ break; }
        for(int j = 0; j < row_width - 1 && j < strlen(str); j++){
            if(str[j] == '\n'){ break; }
            *(pos + (j+1)*CHUNK) = str[j];
            *(pos + (j+1)*CHUNK + 1) = '\0';
            *(pos + (j+1)*CHUNK + 2) = '\0';
            *(pos + (j+1)*CHUNK + 3) = '\0';
        }
        pos += book->pages->ws.width * CHUNK;
    }
    pos = book->pages->buf + (book->pages->ws.width + row_width + 2) * CHUNK; 
    for(int i = 0; i < row_amt; i++){
        if(feof(book->fptr)){ break; }
        fgets(str, row_width, book->fptr);
        if(str == NULL){ break; }
        for(int j = 0; j < row_width && j < strlen(str); j++){
            if(str[j] == '\n'){ break; }
            *(pos + (j + 1)*CHUNK) = str[j];
            *(pos + (j + 1)*CHUNK + 1) = '\0';
            *(pos + (j + 1)*CHUNK + 2) = '\0';
            *(pos + (j + 1)*CHUNK + 3) = '\0';
        }
        pos += book->pages->ws.width * CHUNK;
    }
    book_print_pagenum(book);
    free(str);
}

void book_delete(struct Book** book){
    fclose((*book)->fptr);
    free((*book)->buffer);
    free((*book)->filename);
    frame_delete(&((*book)->pages));
    list_free((*book)->index);
}

int my_log10(long num){
    int cnt = 0;
    do{
        num /= 10;
        cnt++;
    }while(num > 0);
    return cnt;
}

int first_digit(long num){
    while(num >= 10){
        num /= 10;
    }
    return num;
}

void book_print_pagenum(struct Book* book){
    int i = 0;
    int num = 2 * book->pagenum + 1;
    int num_len = my_log10(2*book->pagenum + 1) + 1;

    sprintf(book->pages->buf + (book->pages->ws.height - 3)*book->pages->ws.width*CHUNK, BOTTOM_LEFT);      //need a |-
    for(i = 0; i < num_len; i++){
        sprintf(book->pages->buf + (book->pages->ws.height - 3)*book->pages->ws.width*CHUNK + CHUNK + i*CHUNK, FLOOR);
    }
    sprintf(book->pages->buf + (book->pages->ws.height - 3)*book->pages->ws.width*CHUNK + CHUNK + CHUNK, TOP_RIGHT);
    sprintf(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK + CHUNK + CHUNK, WALL);
    sprintf(book->pages->buf + (book->pages->ws.height - 1)*book->pages->ws.width*CHUNK + CHUNK + CHUNK, BOTTOM_RIGHT); //need a _|_
    for(i = 1; i < num_len; i++){
        *(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK + i*CHUNK) = '0' + first_digit(num);
        *(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK + i*CHUNK + 1) = '\0';
        *(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK + i*CHUNK + 2) = '\0';
        *(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK + i*CHUNK + 3) = '\0';
        num /= 10;
    }

    num = 2* book->pagenum + 2;
    num_len = my_log10(2* book->pagenum + 2);


    sprintf(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK - 1*CHUNK, BOTTOM_RIGHT);      //need a |-
    for(i = 0; i < num_len; i++){
        sprintf(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK - 2*CHUNK - i*CHUNK, FLOOR);
    }
    sprintf(book->pages->buf + (book->pages->ws.height - 2)*book->pages->ws.width*CHUNK - 3*CHUNK , TOP_LEFT);
    sprintf(book->pages->buf + (book->pages->ws.height - 1)*book->pages->ws.width*CHUNK - 3*CHUNK , WALL);
    sprintf(book->pages->buf + (book->pages->ws.height - 0)*book->pages->ws.width*CHUNK - 3*CHUNK , BOTTOM_LEFT); //need a _|_
    for(i = 0; i < num_len; i++){
        *(book->pages->buf + (book->pages->ws.height - 1)*book->pages->ws.width*CHUNK - 2*CHUNK - i*CHUNK) = '0' + num % 10;
        *(book->pages->buf + (book->pages->ws.height - 1)*book->pages->ws.width*CHUNK - 2*CHUNK - i*CHUNK + 1) = '\0';
        *(book->pages->buf + (book->pages->ws.height - 1)*book->pages->ws.width*CHUNK - 2*CHUNK - i*CHUNK + 2) = '\0';
        *(book->pages->buf + (book->pages->ws.height - 1)*book->pages->ws.width*CHUNK - 2*CHUNK - i*CHUNK + 3) = '\0';
        num /= 10;
    }
}
