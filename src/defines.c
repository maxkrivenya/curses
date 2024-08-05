#include "./headers/defines.h"

void ERROR(char* s){
    if(s != NULL){
        printf("%s%sERROR:%s%s\n", BACK_BLACK, FORE_RED, s, RESET);
    }
    else{
        printf("%s%sERROR:UNKNOWN%s\n", BACK_BLACK, FORE_RED, RESET);
    }
}

void SUCCESS(char* s){
    if(s != NULL){
        printf("%s%sSUCCESS:%s%s\n", BACK_BLACK, FORE_GREEN, s, RESET);
    }
    else{
        printf("%s%sSUCCESS:UNKNOWN%s\n", BACK_BLACK, FORE_GREEN, RESET);
    }
}
