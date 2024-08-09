#include "./frame.h"
#include "winsize.h"

struct Book{
    char* filename;
    char* buffer;
    FILE* fptr;
    struct Frame* pages;
};

struct Book* book_new(char* filename){
    FILE* fptr = fopen(filename, "r");
    if(fptr == NULL){
        return NULL;
    }
    struct Book* book = (struct Book*)calloc(1, sizeof(struct Book));
    book->pages     = frame_console_new(BACK_BLACK, FORE_YELLOW, filename);
    book->buffer    = (char*)calloc(book->pages->ws.width * book->pages->ws.height * CHUNK, sizeof(char));
    book->filename  = (char*)calloc(STRLEN_MAX, sizeof(char));
    book->fptr      = fptr;
    return book;
}

void book_pages_load(struct Book* book){
    if(book == NULL){ return; }
    if(book->fptr == NULL){ return; }
    if(book->buffer == NULL){ return; }
    if(book->filename == NULL){ return; }
    int row_width = (book->pages->ws.width   - 4) / 2;
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

    pos = book->pages->buf + (book->pages->ws.width + 1) * CHUNK; 
    for(int i = 0; i < row_amt; i++){
        if(feof(book->fptr)){ break; }
        fgets(str, row_width, book->fptr);
        if(str == NULL){ break; }
        for(int j = 0; j < row_width && j < strlen(str); j++){
            if(str[j] == '\n'){ break; }
            *(pos + j*CHUNK) = str[j];
            *(pos + j*CHUNK + 1) = '\0';
            *(pos + j*CHUNK + 2) = '\0';
            *(pos + j*CHUNK + 3) = '\0';
        }
        pos += book->pages->ws.width * CHUNK;
    }
    for(int i = 0; i < row_width; i++){
        printf("a");
    }
    printf("\n");
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
    free(str);
}

void book_delete(struct Book** book){
    fclose((*book)->fptr);
    free((*book)->buffer);
    free((*book)->filename);
    frame_delete(&((*book)->pages));
}
