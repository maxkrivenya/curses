#include "./headers/defines.h"


void ERROR_LEVEL(char* s, int level){
    printf("\n");
    for(int i = 0; i < level; i++){
        printf("\t");
    }
    if(s != NULL){
        printf("%s%sERROR:%s%s\n", BACK_BLACK, FORE_RED, s, RESET);
    }
    else{
        printf("%s%sERROR:UNKNOWN%s\n", BACK_BLACK, FORE_RED, RESET);
    }
}
#ifdef linux
void ERROR(char* s){
    ERROR_LEVEL(s, 0);
}
#endif

void SUCCESS_LEVEL(char* s, int level){
    printf("\n");
    for(int i = 0; i < level; i++){
        printf("\t");
    }
    if(s != NULL){
        printf("%s%sSUCCESS:%s%s\n", BACK_BLACK, FORE_GREEN, s, RESET);
    }
    else{
        printf("%s%sSUCCESS:UNKNOWN%s\n", BACK_BLACK, FORE_GREEN, RESET);
    }
}

void SUCCESS(char* s){
    SUCCESS_LEVEL(s, 0);
}
