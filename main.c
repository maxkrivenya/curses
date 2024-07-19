#include "frame.h"

int main(){

    console = new_console_full(BACK_BLUE, FORE_CYAN, "helo world!");

    struct WinSize f1040 = {20,80};
    struct Frame* frame1 = new_frame(f1040, BACK_BLACK, FORE_YELLOW, "frame1");

    //print_frame(console);
    //sleep(5);
    render_frame(frame1, 0);
    print_frame(console);


    delete_frame(&console);
    delete_frame(&frame1);
    printf("\n\n");
    return 0;
}


void color_play(){
    char input = '\0';
    char* flush = (char*)calloc(1000, sizeof(char));
    while(1){
        print_frame(console);

        flush = fgets(flush, 3, stdin);
        input = '\0';
        while(!isdigit(input) && !isalpha(input)){
            input = fgetc(stdin);
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
