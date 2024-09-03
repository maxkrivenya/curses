#include "./headers/frame.h"
#include "./headers/action.h"


/*--------------------setters---------------------------*/
void frame_set_is_focus(struct Frame* fr, int val){
    fr->details.is_focus = val;
}

void frame_set_bc(struct Frame* fr, const char* bc){
    fr->bc = bc;
}

void frame_set_fc(struct Frame* fr, const char* fc){
    fr->fc = fc;
}

void frame_cursor_set(struct WinSize pos, int offset){
    printf("\033[%d;%dH", pos.height + 1, pos.width + 1 + offset);
}

void frame_write(struct Frame* fr, int pos, char val){
    *(fr->buf + pos*CHUNK) = val;
}

/*------------------------------------------------------*/

void frame_print_corners(struct Frame* fr){
    if(fr->buf == NULL){return;}
    sprintf(fr->buf, TOP_LEFT);
    sprintf(fr->buf + (fr->ws.width - 1) * CHUNK, TOP_RIGHT);
    sprintf(fr->buf + fr->ws.width * (fr->ws.height - 1) * CHUNK, BOTTOM_LEFT);
    sprintf(fr->buf + fr->ws.width * fr->ws.height * CHUNK - CHUNK, BOTTOM_RIGHT);
}

void frame_print_walls(struct Frame* fr){
    if(fr->buf == NULL){return;}
    for(int i = 1; i < fr->ws.height - 1; i++){
        sprintf(fr->buf + i * fr->ws.width * CHUNK, WALL);
        sprintf(fr->buf + (i + 1) * fr->ws.width * CHUNK  - CHUNK, WALL);
    }
}
void frame_print_floors(struct Frame* fr){
    if(fr->buf == NULL){return;}
    for(int i = 1; i < fr->ws.width - 1; i++){
        sprintf(fr->buf + i * CHUNK, FLOOR);
        sprintf(fr->buf + i * CHUNK + fr->ws.width * (fr->ws.height - 1) * CHUNK,FLOOR);
    }
}

void frame_print_name(struct Frame* fr){
    if(fr->buf == NULL){return;}
    if(fr->name == NULL){return;}
    int offset = ( fr->ws.width - strlen(fr->name) - 2) / 2 ;
    offset = offset - offset % CHUNK;
    offset *= CHUNK;

    fr->buf[offset - CHUNK] = '[';
    for(int i = 1; i < CHUNK; i++){
        fr->buf[offset - CHUNK + i] = '\0';
    }
    for(int i = 0; i < strlen(fr->name) && i < WORDLEN_MAX; i++){
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

void* frame_handle_action(struct Frame* frame_ptr, struct Frame* field_ptr, char trigger){
    struct Action* act;
    act = frame_get_action(field_ptr, trigger);
    if(act == NULL){ act = frame_get_action(frame_ptr, trigger);}
    if(act != NULL){ 
        return act->action(act->parent, act->parameters);
    }
    return NULL;
}

/*------------------------------------------------------*/

struct Frame* frame_new(char* filepath, struct WinSize ws, int rows, int cols, const char* bc, const char* fc, char* frame_name){
    struct Frame* fr = (struct Frame*)calloc(1, sizeof(struct Frame));
    fr->ws.width = ws.width;
    fr->ws.height = ws.height;
    fr->bc = bc;
    fr->fc = fc;
    fr->col = cols;
    fr->row = rows;
    fr->buf = (char*)calloc(fr->ws.height * fr->ws.width, CHUNK);
    fr->fields = ring_new();
    fr->events = list_new();
    if(filepath != NULL){
        fr->filepath = (char*)calloc(strlen(filepath), sizeof(char));

        for(int i = 0; i < strlen(filepath); i++){
            fr->filepath[i] = filepath[i];
        }
    }

    if(frame_name != NULL){
        fr->name = (char*)calloc(strlen(frame_name), sizeof(char));
        for(int i = 0; i < strlen(frame_name) && i < WORDLEN_MAX; i++){
            fr->name[i] = frame_name[i];
        }
    }

    for(int i = 0; i < fr->ws.width * fr->ws.height; i++){
        fr->buf[i * CHUNK] = ' ';
    }

    if(!cols && !rows){
        frame_print_corners(fr);
        frame_print_walls(fr);
        frame_print_floors(fr);
        frame_print_name(fr);
    }

    return fr;
}

struct Frame* frame_new_default(char* id, struct WinSize ws, int rows, int cols){

    return frame_new(id, ws, rows, cols, BACK_BLUE, FORE_CYAN, NULL);
}

struct Frame* frame_console_new(const char* bc, const char* fc, char* name){
    return frame_new("console\0", get_console_size(), 0, 0, bc, fc, name);    
}

struct Frame* frame_console_new_no_name(const char* bc, const char* fc){
    if(bc != NULL && fc != NULL){
        return frame_new("console\0", get_console_size(), 0, 0, bc, fc, NULL);
    }else{
        return frame_new_default("console\0", get_console_size(), 0, 0);
    }
}

struct Frame* frame_console_new_default(){
    return frame_new_default("console\0", get_console_size(), 0, 0);
}


void frame_delete(struct Frame** frame){
    struct Frame* fr = *frame;
    if(fr->buf != NULL){ free(fr->buf); }
    if(fr->name != NULL){ free(fr->name); }
    if(fr->filepath != NULL){ free(fr->filepath); }
    ring_free(fr->fields);
    list_free(fr->events);

}

void frame_get_screen_value(struct Frame* fr, char* dest){
    int i = 0;
    
    while(i < fr->ws.width * fr->ws.height){
            if(!isalpha(fr->buf[i* CHUNK]) && !isdigit(fr->buf[i*CHUNK])){
                *(dest + i) = '\0';
                return;
            }
            *(dest + i) = *(fr->buf + i * CHUNK);
            i++;
    }
}



void frame_globals_update(struct Frame* parent, struct Frame* new){
    if(new->fields == NULL){
        new->fields = ring_new();
    }
    new->details.global_col = parent->details.global_col + new->col;
    new->details.global_row = parent->details.global_row + new->row;
    struct Node* nptr = new->fields->head;
    while(nptr != NULL){
        frame_globals_update(new, ((struct Frame*)(nptr->value)));
        nptr = nptr->next;
        if(nptr == new->fields->head){ break; }
    }
}

/*--------------------------------------------------------*/

void frame_clear(struct Frame* fr){
    for(int i = 0; i < fr->ws.width * fr->ws.height; i++){
        fr->buf[i * CHUNK] = ' ';
    }
    frame_print_corners(fr);
    frame_print_walls(fr);
    frame_print_floors(fr);
    frame_print_name(fr);
}

struct Node* frame_find_closest_field(struct Frame* fr, int row, int cur, int level){
    if(fr               == NULL){return NULL;}
    if(fr->fields        == NULL){return NULL;}
    if(fr->fields->head  == NULL){return NULL;}
    cur /= CHUNK;

    int i =  fr->ws.width;
    struct Node* from_ring = 0;
    struct Node* ret = NULL;
    struct Ring* ring = fr->fields; 
    struct Node* nptr = ring->head;

    do{
        if(((struct Frame*)(nptr->value))->row <= row && row < (((struct Frame*)(nptr->value))->row + ((struct Frame*)(nptr->value))->ws.height)){
            if(((struct Frame*)(nptr->value))->col > cur && i > ((struct Frame*)(nptr->value))->col - cur){
                i = ((struct Frame*)(nptr->value))->col - cur;
                ret = nptr;
                /*
            }else{
                if(((struct Frame*)(nptr->value))->fields != NULL){
                    from_ring = frame_find_closest_field(((struct Frame*)(nptr->value)), row - ((struct Frame*)(nptr->value))->row, cur - ((struct Frame*)(nptr->value))->col, level + 1);
                    if(from_ring != NULL){
                        if( i > ((struct Frame*)(nptr->value))->col + ((struct Frame*)(from_ring->value))->col - cur){
                            i = ((struct Frame*)(nptr->value))->col + ((struct Frame*)(from_ring->value))->col - cur;
                            ret = from_ring;
                        }
                    }
                }

            */
            }
        }
        if(level == 0) { break; }
        nptr = nptr->next;
    }while(nptr != ring->head);

    return ret;
}

struct Node* frame_get_first_field_node(struct Ring* ring){
    if(ring == NULL) {return NULL; }
    if(ring->head == NULL) { return NULL; }
    if(ring->head->value == NULL) { return NULL; }
    struct Node* ret = frame_get_first_field_node(((struct Frame*)(ring->head->value))->fields);
    if(ret != NULL){
        return ret;
    }
    return ring->head;
}


int frame_print_row(struct Frame* fr, int row, int col, int level){
    if(fr->buf == NULL){printf("NUULL\n"); return 0;}
    int i = row - fr->row;
    int j = 0;
    struct Node* next = NULL;
    int write_until = 0;

    if(fr->details.is_field){
        if(fr->name != NULL){
            for(int k = 0; k < strlen(fr->name); k++){
                printf("%c", fr->name[k]);
            }
        }
    }
    printf("%s%s", fr->bc, fr->fc);
    if(fr->details.is_focus == 1){
        printf(RESET);
        printf("%s%s", BACK_CYAN, FORE_YELLOW);
    }
    do{
        next = frame_find_closest_field(fr, i, j, level);

        if(next == NULL){
            write_until = fr->ws.width;
        }else{
            write_until = ((struct Frame*)(next->value))->col;
        }

        for(; j < write_until * CHUNK; j++){
            printf("%c", *(fr->buf + (i*fr->ws.width)*CHUNK + j));
        }

        if(next != NULL){
            frame_print_row(((struct Frame*)(next->value)), row - fr->row, 0, level + 1);
            if(((struct Frame*)(next->value))->details.is_field){
                if(((struct Frame*)(next->value))->name != NULL){
                    j += (((struct Frame*)(next->value))->ws.width + strlen(((struct Frame*)(next->value))->name))* CHUNK;
                }
                }else{
                    j += (((struct Frame*)(next->value))->ws.width)* CHUNK;

                }
                printf("%s%s", fr->bc, fr->fc);
            }else{
                printf("%s%s", fr->bc, fr->fc);
                if(fr->details.is_focus == 1){
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

void frame_print(struct Frame* fr){
    if(fr == NULL){return;}
    fr->ws = get_console_size();

    printf("\n");

    long size = fr->ws.width * fr->ws.height * CHUNK;

    for(int i = 0; i < fr->ws.height; i++){
        frame_print_row(fr, i, 0, 0);
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

struct Action* frame_event_taken(struct Frame* fr, char trigger){
    if(fr == NULL){return NULL;}
    if(fr->events == NULL){ return NULL; }
    if(fr->events->head == NULL){ return NULL; }
    struct Node* nptr = fr->events->head;
    while(nptr != NULL){
        if(((struct Action*)nptr->value)->trigger == trigger){
            return nptr->value;
        }
        nptr = nptr->next;
    }
    return NULL;
}

void frame_push_field(struct Frame* dest, struct Frame* fr){
    if(dest == NULL || fr == NULL){ return; }
    if(dest->fields == NULL){ dest->fields = ring_new(); }
    if(!fr->row || !fr->col){
        fr->row = (dest->ws.height - fr->ws.height) / 2;
        fr->row = fr->row - fr->row % CHUNK;
        fr->col = (dest->ws.width - fr->ws.width) / 2;
        fr->col = fr->col - fr->col % CHUNK;
        fr->details.is_field = 0;
    }
    else{
        fr->details.is_field = 1;
    }

    frame_globals_update(dest, fr);

    ring_push(dest->fields, node_new(fr));

}

void frame_push_event(struct Frame* dest, struct Action* action){
    if(dest == NULL || action == NULL){ return; }
    if(dest->events == NULL){ dest->events = list_new(); }
    struct Action* nptr = frame_event_taken(dest, action->trigger);
    if(nptr != NULL){
        //ERROR("EVENT ALREADY TAKEN");
        return;
    }
    action->parent = dest;
    list_push_tail(dest->events, node_new(action));
}

struct WinSize frame_cursor_get(struct Frame* fr, struct Frame* x){
    struct WinSize ws = {0,0};
    if(fr == NULL || x == NULL){ return ws; }
    if(fr->fields == NULL) { return ws; }
    if(fr->fields->head == NULL) { return ws; }

    struct Node* nptr = fr->fields->head;
    do{
        if(((struct Frame*)(nptr->value)) == x){
            ws.height = fr->row + x->row;
            if(x->details.is_field){
                ws.width  = fr->col + x->col + strlen(x->name);
            }
            return ws;
        }else{
            if(((struct Frame*)(nptr->value))->fields != NULL){
                ws = frame_cursor_get(((struct Frame*)(nptr->value)), x);
                if(ws.width > 0 &&  ws.height > 0){
                    if(ws.height != ((struct Frame*)(nptr->value))->row && ws.width != ((struct Frame*)(nptr->value))->col){
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

char rm_ctrl(char input){
    switch(input){
        case '+':{
                     return input;
                 }
        default:{
                    return 0;
                }
    }
}

struct Frame* frame_new_from_file(char* src){
    struct Frame* field = NULL;

    int row = 0;
    int col = 0;
    int height =0;
    int width = 0;
    char* bc = NULL;
    char* fc = NULL;
    int is_field = 0;
    int file_row = 0;
    char* name = (char*)calloc(WORDLEN_MAX, sizeof(char));

    FILE* fptr = fopen(src, "r");
    if(fptr == NULL){
        printf("src is empty!");
        return NULL;
    }

    struct Ring* ring = ring_new();

    char* str = (char*)calloc(STRLEN_MAX, sizeof(char));
    char* word = (char*)calloc(WORDLEN_MAX, sizeof(char));
    if(str == NULL){return NULL;}
    if(word == NULL){return NULL;}
    if(name == NULL){return NULL;}
    int len = 0;
    int i = 0;
    do{
        if(fgets(str, STRLEN_MAX - 1, fptr) != NULL){
            for(i = 0; i < WORDLEN_MAX; i++){ word[i] = '\0'; }
            len = strlen(str);

            for(i = len - 1; i > 0 && str[i] != ' ' && str[i] != '='; i--);
            i++;

            for(int j = i; j < len && str[j] != '\n'; j++){
                word[j - i] = str[j];
            } 
            word[WORDLEN_MAX - 1] = '\0';
            if(str[0] != '\n' && str[0] != '\0'){
                switch(str[0]){
                    case 'S': {
                                  if(file_row > 1){
                                      FILE* ftmp = fopen("frames/tmp.fr", "w");
                                      if(ftmp != NULL){ 
                                          do{
                                              fputs(str, ftmp);
                                              if(fgets(str, STRLEN_MAX, fptr) == NULL){
                                                  break;
                                              }
                                          }while(!feof(fptr) && str[0] != 'E');
                                          fputs(str, ftmp);
                                          fclose(ftmp);
                                          field = frame_new_from_file("frames/tmp.fr");
                                          field->details.is_field = 1;
                                          ring_push(ring, node_new(field));
                                      }
                                  }
                              }
                              break;
                    case 'W': { width     = atoi(word); break; }
                    case 'H': { height    = atoi(word); break; }
                    case 'R': { row       = atoi(word); break; }
                    case 'C': { col       = atoi(word); break; }
                    case 'N':{
                                 for(int i = 0; i < strlen(word) && i < WORDLEN_MAX; i++){ 
                                     name[i] = word[i]; 
                                 }
                                 name[strlen(word)] = '\0';
                             }
                    case 'B':{
                                 switch(word[0]){
                                     case 'R': bc = BACK_RED; break;
                                     case 'B': {
                                                   if(word[1] == 'L'){
                                                       if(word[2] == 'U'){
                                                           bc = BACK_BLUE;
                                                       }
                                                       if (word[2] == 'A') {
                                                           bc = BACK_BLACK;
                                                       }
                                                   }
                                                   break;
                                               }
                                     case 'C': bc = BACK_CYAN; break;
                                     case 'G': bc = BACK_GREEN; break;
                                     case 'W': bc = BACK_WHITE; break;
                                     case 'M': bc = BACK_MAGENTA; break;
                                     default:break;
                                 }
                                 break;
                             }
                    case 'F':{
                                 switch(word[0]){
                                     case 'R': fc = FORE_RED; break;
                                     case 'B': {
                                                   fc = FORE_BLUE;
                                                   break;
                                               }
                                     case 'C': fc = FORE_CYAN; break;
                                     case 'G': fc = FORE_GREEN; break;
                                     case 'M': fc = FORE_MAGENTA; break;
                                     case 'Y': fc = FORE_YELLOW; break;
                                     default:break;
                                 }
                                 break;
                             }
                    default: break;
                }
            }
        }
        file_row++;
    }while(!feof(fptr));
    if(fptr != NULL){
        fclose(fptr);
    }

    struct Frame* new = frame_new(src, get_winsize(height, width), row, col, bc, fc, name);
    new->details.global_col = new->col;
    new->details.global_row = new->row;
    if(new->bc != NULL){
        new->bc = bc;
    }else{
        new->bc = BACK_BLUE;
    }
    if(fc != NULL){
        new->fc = fc;
    }else{
        new->fc = FORE_CYAN;
    }
    new->fields = ring;
    if(ring->head != NULL){
        if(ring->head->next == ring->head){
            ((struct Frame*)(ring->head->value))->details.global_col = ((struct Frame*)(ring->head->value))->details.global_col + new->details.global_col;
            ((struct Frame*)(ring->head->value))->details.global_row = ((struct Frame*)(ring->head->value))->details.global_row + new->details.global_row;
        }else{
            struct Node* nptr = ring->head->next;
            do{
                ((struct Frame*)(nptr->value))->details.global_col = ((struct Frame*)(nptr->value))->details.global_col + new->details.global_col;
                ((struct Frame*)(nptr->value))->details.global_row = ((struct Frame*)(nptr->value))->details.global_row + new->details.global_row;
                nptr = nptr->next;
            }while(nptr != ring->head);
        }
    }

    free(name);
    free(str);
    free(word);
return new;
}

void frame_next_field(struct Node** frame_ptr, struct Node** field_ptr, struct WinSize* pos){

    frame_set_is_focus(((struct Frame*)((*(field_ptr))->value)), 0);

    ring_next(((struct Frame*)((*frame_ptr)->value))->fields);
    *(field_ptr) = ((struct Frame*)((*frame_ptr)->value))->fields->head;

    frame_set_is_focus(((struct Frame*)((*(field_ptr))->value)), 1);

    *pos = frame_cursor_get((struct Frame*)((*frame_ptr)->value), ((struct Frame*)((*(field_ptr))->value)));
    frame_cursor_set(*pos, 0);

}

struct Action* frame_get_action(struct Frame* fr, char trigger){
    if(fr == NULL){
        ERROR("FRAME IS NULL");
        return NULL;
    }
    if(fr->events == NULL){
        ERROR("NO EVENTS");
        return NULL;
    }
    if(fr->events->head == NULL){return NULL;}

    struct Node* nptr;
    struct Action* act;

    nptr = fr->events->head;

    do{
        act = ((struct Action*)(nptr->value));
        if(act->trigger == trigger){
            return act;
        }
        nptr = nptr->next;
    }while(nptr != NULL);
    return NULL;
}

