#include "defines.h"


struct Frame{
    char* name;
    struct WinSize ws;
    char* buf;
    const char* fc;
    const char* bc;
    struct List* field;
};
struct Frame* console;

/*------------------------------------------------------*/

void corners(struct Frame* fr){
    if(fr->buf == NULL){return;}
    sprintf(fr->buf, TOP_LEFT);
    sprintf(fr->buf + (fr->ws.width - 1) * CHUNK, TOP_RIGHT);
    sprintf(fr->buf + fr->ws.width * (fr->ws.height - 1) * CHUNK, BOTTOM_LEFT);
    sprintf(fr->buf + fr->ws.width * fr->ws.height * CHUNK - CHUNK, BOTTOM_RIGHT);
}

void walls(struct Frame* fr){
    if(fr->buf == NULL){return;}
    for(int i = 1; i < fr->ws.height - 1; i++){
       sprintf(fr->buf + i * fr->ws.width * CHUNK, WALL);
       sprintf(fr->buf + (i + 1) * fr->ws.width * CHUNK  - CHUNK, WALL);
    }
}
void floors(struct Frame* fr){
    if(fr->buf == NULL){return;}
    for(int i = 1; i < fr->ws.width - 1; i++){
       sprintf(fr->buf + i * CHUNK, FLOOR);
       sprintf(fr->buf + i * CHUNK + fr->ws.width * (fr->ws.height - 1) * CHUNK,FLOOR);
    }
}

void name(struct Frame* fr){

    if(fr->buf == NULL){return;}
    if(fr->name == NULL){return;}
    int offset = ( fr->ws.width - strlen(fr->name) - 2) / 2 ;
    offset = offset - offset % CHUNK;
    offset *= CHUNK;

    fr->buf[offset - CHUNK] = '[';
    for(int i = 1; i < CHUNK; i++){
        fr->buf[offset - CHUNK + i] = '\0';
    }
    for(int i = 0; i < strlen(fr->name); i++){
        fr->buf[offset + i*CHUNK] = fr->name[i];
        for(int j = 1; j < CHUNK; j++){
            fr->buf[offset + i*CHUNK + j] = '\0';
        }

    }
    fr->buf[offset + strlen(fr->name)  * CHUNK] = ']';
    for(int i = 1; i < CHUNK; i++){
        fr->buf[offset + strlen(fr->name) * CHUNK + i] = '\0';
    }
}

/*------------------------------------------------------*/

struct Frame* new_frame(struct WinSize ws, const char* bc, const char* fc, char* frame_name){
    struct Frame* fr = (struct Frame*)calloc(1, sizeof(struct Frame));
    fr->ws.width = ws.width;
    fr->ws.height = ws.height;
    fr->bc = bc;
    fr->fc = fc;
    fr->buf = (char*)calloc(fr->ws.height * fr->ws.width, CHUNK);

    if(frame_name != NULL){
        fr->name = (char*)calloc(strlen(frame_name), sizeof(char));
        for(int i = 0; i < strlen(frame_name); i++){
            fr->name[i] = frame_name[i];
        }
    }

    for(int i = 0; i < fr->ws.width * fr->ws.height; i++){
        fr->buf[i * CHUNK] = ' ';
    }

    corners(fr);
    walls(fr);
    floors(fr);
    name(fr);

    return fr;
}

struct Frame* new_default_frame(struct WinSize ws){

    return new_frame(ws, BACK_BLUE, FORE_CYAN, NULL);
}

struct Frame* new_console_full(const char* bc, const char* fc, char* name){
    return new_frame(get_console_size(), bc, fc, name);    
}

struct Frame* new_console_noname(const char* bc, const char* fc, char* name){
    if(bc != NULL && fc != NULL){
        return new_frame(get_console_size(), bc, fc, NULL);
    }else{
        return new_default_frame(get_console_size());
    }
}

struct Frame* new_default_console(){
    return new_default_frame(get_console_size());
}


void delete_frame(struct Frame** frame){
    struct Frame* fr = *frame;
    if(fr->name != NULL){ free(fr->name); }
    if(fr->buf != NULL){ free(fr->buf); }
}



/*--------------------------------------------------------*/

void print_frame(struct Frame* fr){

    printf("\n");
    printf("%s%s", fr->bc, fr->fc);
    system("clear");
    /*

    int offset = ( fr->ws.width - strlen(fr->name) - 2) * CHUNK / 2;
    int i = 0;

    for(int i = 0; i < offset; i++){
        printf("%c", fr->buf[i]);
    }

    printf("[");
    for(int i = 0; i < strlen(fr->name); i++){
        printf("%c\0\0\0", fr->name[i]);
    }
    printf("]");

    i = offset + (strlen(fr->name) + 2) * CHUNK;
    for(; i < fr->ws.width * fr->ws.height * CHUNK; i++){
        printf("%c", fr->buf[i]);
    }
    */
    for(int i = 0; i <= fr->ws.width * fr->ws.height * CHUNK; i++){
        printf("%c", fr->buf[i]);
    }

    printf("%s", RESET);
}

void render_frame(struct Frame* fr, int lvl){
    if(fr->bc != NULL){
        console->bc = fr->bc;
    }
    if(fr->fc != NULL){
        console->fc = fr->fc;
    }

    //TODO: check for lvl
    

    int i_diff = (console->ws.height - fr->ws.height) / 2;
    i_diff = i_diff - (i_diff % CHUNK);
    int j_diff = (console->ws.width - fr->ws.width )/ 2;
    j_diff = j_diff - (j_diff % CHUNK);

    int rows_skip = (i_diff + lvl) * console->ws.width * CHUNK;
    int cols_skip = (j_diff + lvl) * CHUNK;

    for(int i = 0; i < fr->ws.height; i++){
        for(int j = 0; j < fr->ws.width * CHUNK; j++){
            *(console->buf + (rows_skip + i*console->ws.width*CHUNK) + (cols_skip + j)) = *(fr->buf + (i * fr->ws.width * CHUNK) + (j));
        }
    }
}
