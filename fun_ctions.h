#include "list.h"

void color_play(struct Frame* console){
    char input = '\0';
    char* flush = (char*)calloc(1000, sizeof(char));
    while(1){
        frame_print(console);

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

void running_frame(struct Frame* console, struct Frame* fr){
    int turn = 0;

    struct Node* node = node_new(fr);

    push_field(console->field, node);
    for(int i = 0; i < 8; i++){
        turn = i % 4;

        switch(turn){
            case 0: { console->field->head->fr->row += 30; break; }
            case 1: { console->field->head->fr->col += 100; break; }
            case 2: { console->field->head->fr->row -= 30; break; }
            case 3: { console->field->head->fr->col -= 100; break; }
            default: break;
        }
        system("clear");
        frame_print(console);

        sleep(1);
    }

}

/*
void play_frame(struct Frame* console, struct Frame fr, int lvl){
    char input = '\0';
    struct WinSize ws1 = {console->ws.height/2, console->ws.width/2};
    struct Frame* frame1;
    switch(lvl){
        case 0 :{ frame1 = new_frame(ws1, 0, 0, BACK_BLUE, FORE_CYAN, "frame1"); break;}
        case 1: { frame1 = new_frame(ws1, 0, 0, BACK_BLACK, FORE_YELLOW, "frame1");break; }
        default:{ frame1 = new_frame(ws1, 0, 0, BACK_RED, FORE_GREEN, "frame1");break;}
    }
    push(console, frame1);
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

*/

void hacker_screen(){
    struct WinSize ws = get_console_size();
    char* buf = (char*)calloc(ws.width * ws.height, sizeof(char));

    for(int i = 0; i < ws.width * ws.height; i++){
        buf[i] = 'a' + rand()%26;
    }
    int l = 0;

    printf("%s", FORE_GREEN);

    do{
        l++;
        system("clear");
        
        puts(buf);
        for(int i = ws.height * ws.width - 1; i > ws.width; i--){
                *(buf + i) = *(buf + i - ws.width);
        }
        for(int i = 0; i < ws.width; i++){
            buf[i] = 'a' + rand()%26;
        }
        usleep(50000);
    }while(l < 1000);

    printf(RESET);
    free(buf);
}

void rain(){
	struct WinSize ws = get_console_size();
	char* buf = (char*)calloc(ws.width * ws.height, sizeof(char));

	for(int i = 0; i < ws.width * ws.height; i++){
		buf[i] = ' ';
	}
    int l = 0;
    int sped_up[ws.width/3];  // (int*)calloc(ws.width/2, sizeof(int));
    int is_sped_up = 0;

    printf("%s", FORE_CYAN);
    do{
        for(int i = 0; i < ws.width / 3; i++){
            sped_up[i] = rand()%ws.width;
        }
        l++;
        system("clear");

        puts(buf);
        for(int i = ws.width - 1; i > 0; i--){
            is_sped_up = 0;
            for(int k = 0; k < ws.width/3; k++){
                if(sped_up[k] == i){
                    is_sped_up = 1;
                    break;
                }
            }
            if(is_sped_up){
                for(int j = ws.height - 1; j > 1; j--){
                    *(buf + (j * ws.width) + i) = *(buf + ((j-2) * ws.width) + i);
                }
                *(buf + ws.width + i) = ' '; 
            }else{
                for(int j = ws.height - 1; j > 0; j--){
                    *(buf + (j * ws.width) + i) = *(buf + ((j-1) * ws.width) + i);
                }
            }
        }
        for(int i = 0; i < ws.width; i++){
            if(rand()%25){
                buf[i] = ' ';
            }else{
                buf[i] = '|';
            }
        }
        usleep(50000);
    }while(l < 100);

    printf(RESET);
	free(buf);
}

