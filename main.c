#include "list.h"

void color_play(struct Frame* console){
    char input = '\0';
    char* flush = (char*)calloc(1000, sizeof(char));
    while(1){
        print_frame(console);

        flush = fgets(flush, 3, stdin);
        input = '\0';
        while(!isdigit(input) && !isalpha(input)){
            input = getc(stdin);
        }
        switch(input){
            case '1': { console->fc = FORE_RED; break;}
            case '2': { console->fc = FORE_GREEN; break;}
            case '3': { console->fc = FORE_BLUE; break;}
            case '4': { console->fc = FORE_YELLOW; break;}
            case '5': { console->fc = FORE_CYAN; break;}
            case '6': { console->fc = FORE_MAGENTA; break;}
            case 'q': { console->bc = BACK_RED; break;}
            case 'w': { console->bc = BACK_GREEN; break;}
            case 'e': { console->bc = BACK_BLUE; break;}
            case 'r': { console->bc = BACK_YELLOW; break;}
            case 't': { console->bc = BACK_CYAN; break;}
            case 'y': { console->bc = BACK_MAGENTA; break;}
            default : { free(flush); return;  }
        }

    }
}

void play_frame(struct Frame* console, struct Frame fr, int lvl){
    char input = '\0';
    struct WinSize ws1 = {console->ws.height/2, console->ws.width/2};
    struct Frame* frame1;
    switch(lvl){
        case 0 :{ frame1 = new_frame(ws1, BACK_BLUE, FORE_CYAN, "frame1"); break;}
        case 1: { frame1 = new_frame(ws1, BACK_BLACK, FORE_YELLOW, "frame1");break; }
        default:{ frame1 = new_frame(ws1, BACK_RED, FORE_GREEN, "frame1");break;}
    }
    render_frame_to_frame(&fr, frame1, lvl + 1); 
    while(1){
        print_frame(&fr);
        input = '\0';
        input = getc(stdin);
        switch(input){
            case '+': { play_frame(console, fr, lvl + 1); break;}
            case '-': { return; }
            default : { break;  }
        }

    }
}


void filler(struct Frame* console){
    for(int i = 0; i < console->ws.width * console->ws.height; i++){
        console->buf[CHUNK * i] = ' ';
    }
}

void running_frame(struct Frame* console, struct Frame* fr){
    int turn = 0;

    struct Node* node = get_node(fr, 1, 1,  NULL, NULL);

    push(console->field, node);
    for(int i = 0; i < 8; i++){
        turn = i % 4;

        switch(turn){
            case 0: { console->field->head->row += 30; break; }
            case 1: { console->field->head->col += 100; break; }
            case 2: { console->field->head->row -= 30; break; }
            case 3: { console->field->head->col -= 100; break; }
            default: break;
        }
        print_frame(console);

        sleep(1);
    }

}

int main(){

    struct Frame* console;
    console = new_console_full(BACK_BLUE, FORE_CYAN, "helo world!");

    struct WinSize ws1 = {20, 80};
    struct Frame* frame1 = new_frame(ws1, BACK_BLACK, FORE_YELLOW, "TY PIDOR");

    struct Frame* frame2 = new_frame(ws1, BACK_BLUE, FORE_CYAN, "field");

    /*
    struct Node* node = get_node(frame2, 1, 7, NULL, NULL);
    push(console->field, node);
    struct Node* node1 = get_node(frame2, 1, 55, NULL, NULL);
    push(console->field, node1);
*/

    /*
    render_frame_to_frame(console, frame1, 0);
    print_frame(console);
*/
    running_frame(console, frame1);

    delete_frame(&console);
    delete_frame(&frame1);
    delete_frame(&frame2);

    printf(RESET);
    printf("\n\n");
    return 0;
}



