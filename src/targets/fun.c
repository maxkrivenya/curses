#include "./../headers/framestack.h"

int main(int argc, char* argv[]){
    if(argc > 1){
        char c = getopt(argc, argv, "rh");
        switch(c) {
            case 'r':{ rain(); return 0;}
            case 'h':{ hacker_screen(); return 0;}
            default:{
                        printf("%s%sERROR: UNKNOWN OPT\n%s", BACK_BLACK, FORE_RED, RESET); 
                        return 1;
                    }
        }
    }
    return 0;
}
