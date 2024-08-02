#include "list.h"

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

