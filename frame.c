#include "list.h"

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

struct Frame* new_frame(struct WinSize ws, int rows, int cols, const char* bc, const char* fc, char* frame_name){
    struct Frame* fr = (struct Frame*)calloc(1, sizeof(struct Frame));
    fr->ws.width = ws.width;
    fr->ws.height = ws.height;
    fr->bc = bc;
    fr->fc = fc;
    fr->col = cols;
    fr->row = rows;
    fr->buf = (char*)calloc(fr->ws.height * fr->ws.width, CHUNK);
    fr->field = new_list();

    if(frame_name != NULL){
        fr->name = (char*)calloc(strlen(frame_name), sizeof(char));
        for(int i = 0; i < strlen(frame_name); i++){
            fr->name[i] = frame_name[i];
        }
    }

    for(int i = 0; i < fr->ws.width * fr->ws.height; i++){
        fr->buf[i * CHUNK] = ' ';
    }

    if(!cols && !rows){
        corners(fr);
        walls(fr);
        floors(fr);
        name(fr);
    }

    return fr;
}

struct Frame* new_default_frame(struct WinSize ws, int rows, int cols){

    return new_frame(ws, rows, cols, BACK_BLUE, FORE_CYAN, NULL);
}

struct Frame* new_console_full(const char* bc, const char* fc, char* name){
    return new_frame(get_console_size(), 0, 0, bc, fc, name);    
}

struct Frame* new_console_noname(const char* bc, const char* fc, char* name){
    if(bc != NULL && fc != NULL){
        return new_frame(get_console_size(), 0, 0, bc, fc, NULL);
    }else{
        return new_default_frame(get_console_size(), 0, 0);
    }
}

struct Frame* new_default_console(){
    return new_default_frame(get_console_size(), 0, 0);
}


void delete_frame(struct Frame** frame){
    struct Frame* fr = *frame;
    if(fr->name != NULL){ free(fr->name); }
    if(fr->buf != NULL){ free(fr->buf); }
    free_list(fr->field);

}



/*--------------------------------------------------------*/

struct Node* find_closest_field(struct Frame* fr, int row, int cur, int level){
    if(fr               == NULL){return NULL;}
    if(fr->field        == NULL){return NULL;}
    if(fr->field->head  == NULL){return NULL;}
    cur /= CHUNK;

    int i =  fr->ws.width;
    struct Node* from_list = 0;
    struct Node* ret = NULL;
    struct List* list = fr->field; 
    struct Node* nptr = list->head;

    do{
        if(nptr->fr->row <= row && row < (nptr->fr->row + nptr->fr->ws.height)){
            if(nptr->fr->col > cur && i > nptr->fr->col - cur){
                i = nptr->fr->col - cur;
                ret = nptr;
            }else{
                if(nptr->fr->field != NULL){
                    from_list = find_closest_field(nptr->fr, row - nptr->fr->row, cur - nptr->fr->col, level + 1);
                    if(from_list != NULL){
                        if( i > nptr->fr->col + from_list->fr->col - cur){
                            i = nptr->fr->col + from_list->fr->col - cur;
                            ret = from_list;
                        }
                    }
                }

            }
        }
        if(level == 0) { break; }
        nptr = nptr->next;
    }while(nptr != list->head);

    return ret;
}

struct Node* get_first_field(struct List* list){
    if(list == NULL) {return NULL; }
    if(list->head == NULL) { return NULL; }
    struct Node* ret = get_first_field(list->head->fr->field);
    if(ret != NULL){
        return ret;
    }
    return list->head;
}

int print_row(struct Frame* fr, int row, int col, int level){
    int i = row - fr->row;
    int j = 0;
    struct Node* next = NULL;
    int write_until = 0;

    if(fr->is_field){
        for(int k = 0; k < strlen(fr->name); k++){
            printf("%c", fr->name[k]);
        }
    }
    printf("%s%s", fr->bc, fr->fc);
    if(fr->is_focus == 1){
        printf(RESET);
        printf("%s%s", BACK_CYAN, FORE_YELLOW);
    }
    do{
        next = find_closest_field(fr, i, j, level);

        if(next == NULL){
            write_until = fr->ws.width;
        }else{
            write_until = next->fr->col;
        }

        for(; j < write_until * CHUNK; j++){
            printf("%c", *(fr->buf + (i*fr->ws.width)*CHUNK + j));
        }

        if(next != NULL){
            print_row(next->fr, row - fr->row, 0, level + 1);
            if(next->fr->is_field){
                j += (next->fr->ws.width + strlen(next->fr->name))* CHUNK;
            }else{
                j += (next->fr->ws.width)* CHUNK;

            }
            printf("%s%s", fr->bc, fr->fc);
        }else{
            printf("%s%s", fr->bc, fr->fc);
            if(fr->is_focus == 1){
                printf(RESET);
                printf("%s%s", BACK_CYAN, FORE_YELLOW);
            }
            for(; j < fr->ws.width * CHUNK; j++){
                printf("%c", fr->buf[i * fr->ws.width * CHUNK + j ]);
            }
            printf(RESET);
            return col + j;
        }

    }while(j < fr->ws.width * CHUNK);
            printf(RESET);

    return col + j;
}

void print_frame(struct Frame* fr){
    if(fr == NULL){return;}

    printf("\n");

    long size = fr->ws.width * fr->ws.height * CHUNK;


    if(fr->field != NULL){
        if(fr->field->head != NULL){
            //fr->field->head->fr->is_focus = 1;
        }
    }

    for(int i = 0; i < fr->ws.height; i++){
        print_row(fr, i, 0, 0);
    }

}

void render_frame_to_frame(struct Frame* dest, struct Frame* fr, int lvl){
    if(fr->bc != NULL){
        dest->bc = fr->bc;
    }
    if(fr->fc != NULL){
        dest->fc = fr->fc;
    }

    //TODO: check for lvl


    int i_diff = (dest->ws.height - fr->ws.height) / 2;
    i_diff = i_diff - (i_diff % CHUNK);
    int j_diff = (dest->ws.width - fr->ws.width )/ 2;
    j_diff = j_diff - (j_diff % CHUNK);

    int rows_skip = (i_diff + lvl) * dest->ws.width * CHUNK;
    int cols_skip = (j_diff + lvl) * CHUNK;

    for(int i = 0; i < fr->ws.height; i++){
        for(int j = 0; j < fr->ws.width * CHUNK; j++){
            *(dest->buf + (rows_skip + i*dest->ws.width*CHUNK) + (cols_skip + j)) = *(fr->buf + (i * fr->ws.width * CHUNK) + (j));
        }
    }
}


void push_frame(struct Frame* dest, struct Frame* fr){
    if(dest == NULL || fr == NULL){ return; }
    if(!fr->row || !fr->col){
        fr->row = (dest->ws.height - fr->ws.height) / 2;
        fr->row = fr->row - fr->row % CHUNK;
        fr->col = (dest->ws.width - fr->ws.width) / 2;
        fr->col = fr->col - fr->col % CHUNK;
        fr->is_field = 0;
    }
    else{
        fr->is_field = 1;
    }

    push(dest->field, get_node(fr, NULL, NULL));

}

struct WinSize get_cursor(struct Frame* fr, struct Frame* x){
    struct WinSize ws = {0,0};
    if(fr == NULL || x == NULL){ return ws; }
    if(fr->field == NULL) { return ws; }
    if(fr->field->head == NULL) { return ws; }

    struct Node* nptr = fr->field->head;
    do{
        if(nptr->fr == x){
            ws.height = fr->row + x->row;
            if(x->is_field){
                ws.width  = fr->col + x->col + strlen(x->name);
            }
            return ws;
        }else{
            if(nptr->fr->field != NULL){
                ws = get_cursor(nptr->fr, x);
                if(ws.width > 0 &&  ws.height > 0){
                    if(ws.height != nptr->fr->row && ws.width != nptr->fr->col){
                        ws.height = ws.height + fr->row;
                        ws.width  = ws.width  + fr->col;
                        return ws;
                    }
                }
            }
        }
        nptr = nptr->next;
    }while(nptr != NULL);
    return ws;
}
