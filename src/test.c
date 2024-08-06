#include "./headers/framestack.h"

int frame_assertEqual_level(struct Frame* expected, struct Frame* result, int level){
    printf("\n");
    for(int i = 0; i < level; i++){
        printf("\t");
    }
    printf("{%s\n", expected->name);
    int test_passed = 1;
    int same = 1;

    if(expected->fields == NULL){
        if(result->fields != NULL){
            ERROR_LEVEL("FIELDS ISNT NULL", level + 1);
            test_passed = 0;
        }
    }else{
        if(result->fields == NULL){
            ERROR_LEVEL("FIELDS IS NULL", level + 1);
            test_passed = 0;

        }else{
            if(expected->fields->head == NULL){
                if(result->fields->head != NULL){
                    ERROR_LEVEL("FIELDS ISNT EMPTY", level + 1);
                    test_passed = 0;
                }
            }else{
                struct Node* stopper1 = expected->fields->head;
                struct Node* stopper2 = result->fields->head;
                struct Node* n1 = stopper1;
                struct Node* n2 = stopper2;
                do{
                    if(!frame_assertEqual_level(n1->value, n2->value, level + 1)){
                        ERROR_LEVEL("FIELDS IS DIFFERENT!", level + 1);
                        test_passed = 0;
                        break;
                    }
                    n1 = n1->next;
                    n2 = n2->next;
                }while(n1 != stopper1 && n2 != stopper2 && n1 != NULL && n2 != NULL);
            }
        }
    }

    if(expected->buf == NULL){
        if(result->buf != NULL){
            ERROR_LEVEL("NAME ISNT NULL", level + 1);
            printf("result->buf:%s\n", result->buf);
            test_passed = 0;
        }
    }else{
        if(result->buf == NULL){
            ERROR_LEVEL("NAME IS NULL", level + 1);
            test_passed = 0;
        }
        if(strlen(expected->buf) != strlen(result->buf)){
            ERROR_LEVEL("NAMES ARE DIFFERENT LENGTHS", level + 1);
            printf("%lu:%lu\t%s:%s\n", strlen(expected->buf), strlen(result->buf),  expected->buf, result->buf);
            test_passed = 0;
        }
        for(int i = 0; i < strlen(expected->buf); i++){
            if(expected->buf[i] != result->buf[i]){
                ERROR_LEVEL("NAMES ARE DIFFERENT", level + 1);
                printf("%d, '%s':'%s'\n", i, expected->buf, result->buf);
                test_passed = 0;
            }
        }
    }

    /*
       if(expected->name == NULL){
       if(result->name != NULL){
       ERROR_LEVEL("NAME ISNT NULL", level + 1);
       printf("result->name:%s\n", result->name, level + 1);
       test_passed = 0;
       }
       }else{

       if(result->name == NULL){
       ERROR_LEVEL("NAME IS NULL", level + 1);
       test_passed = 0;
       }
       */
    if(strlen(expected->name) != strlen(result->name)){
        ERROR_LEVEL("NAMES ARE DIFFERENT LENGTHS", level + 1);
        printf("%lu:%lu\t%s:%s\n", strlen(expected->name), strlen(result->name),  expected->name, result->name);
        test_passed = 0;
    }
    for(int i = 0; i < strlen(expected->name); i++){
        if(expected->name[i] != result->name[i]){
            ERROR_LEVEL("NAMES ARE DIFFERENT", level + 1);
            printf("%d, '%s':'%s'\n", i, expected->name, result->name);
            test_passed = 0;
        }
    }

    //}

    /*
       if(expected->fc != result->fc){
       ERROR_LEVEL("FORECOLORS ARE DIFFERENT", level + 1);

       printf("%s%sEXPECTED%s\n", expected->bc, expected->fc, RESET);
       printf("%s%sRESULT%s\n", result->bc, result->fc, RESET);
       printf("%lu:%lu\n", *(long*)expected->fc ,*(long*)result->fc);

       test_passed = 0;
       }

       if(expected->bc != result->bc){
       ERROR_LEVEL("BACKCOLORS ARE DIFFERENT");

       printf("%s%sEXPECTED%s\n", expected->bc, expected->fc, RESET);
       printf("%s%sRESULT%s\n", result->bc, result->fc, RESET);
       printf("%lu:%lu\n", *(long*)expected->bc ,*(long*)result->bc);

       test_passed = 0;
       }

       if(expected->bc != result->bc){
       ERROR_LEVEL("BACKCOLORS ARE DIFFERENT");

       printf("%s%sEXPECTED%s\n", expected->bc, expected->fc, RESET);
       printf("%s%sRESULT%s\n", result->bc, result->fc, RESET);
       printf("%lu:%lu\n", *(long*)expected->bc ,*(long*)result->bc);

       test_passed = 0;
       }
       */
    for(int i = 0; i < WORDLEN_MAX; i++){
        if(expected->filepath[i] != result->filepath[i]){
            ERROR_LEVEL("FILEPATHS ARE DIFFERENT", level + 1);
            for(int i = 0; i <= level; i++){
                printf("\t");
            }
            printf("%d:%c:%c | expected:'%s' | result:'%s'\n", i, expected->filepath[i], result->filepath[i], expected->filepath, result->filepath);
            test_passed = 0;
            break;
        }
    }

    if(expected->ws.width != result->ws.width){
        ERROR_LEVEL("WIDTH IS DIFFERENT", level + 1);
        test_passed = 0;
    }

    if(expected->ws.height != result->ws.height){
        ERROR_LEVEL("HEIGHT IS DIFFERENT", level + 1);
        test_passed = 0;
    }

    if(expected->row != result->row){
        ERROR_LEVEL("ROW IS DIFFERENT", level + 1);
        test_passed = 0;
    }

    if(expected->col != result->col){
        ERROR_LEVEL("COL IS DIFFERENT", level + 1);
        test_passed = 0;
    }

    if(expected->details.is_field != result->details.is_field){
        ERROR_LEVEL("IS_FIELD IS DIFFERENT", level + 1);
        test_passed = 0;
    }

    if(expected->details.is_focus != result->details.is_focus){
        ERROR_LEVEL("IS_FOCUS IS DIFFERENT", level + 1);
        test_passed = 0;
    }

    if(expected->details.global_col != result->details.global_col){
        ERROR_LEVEL("GLOBAL_COL IS DIFFERENT", level + 1);
        printf("%d:%d\n", expected->details.global_col, result->details.global_col);
        test_passed = 0;
    }

    if(expected->details.global_row != result->details.global_row){
        ERROR_LEVEL("GLOBAL_ROW IS DIFFERENT", level + 1);
        printf("%d:%d\n", expected->details.global_row, result->details.global_row);
        test_passed = 0;
    }

    if(test_passed){
        SUCCESS_LEVEL("TEST PASSED!", level + 1);
    }else{
        ERROR_LEVEL("TEST FAILED!", level + 1);
    }
    printf("\n");
    for(int i = 0; i < level; i++){
        printf("\t");
    }
    printf("}\n");

    return test_passed;
}

int frame_assertEqual(struct Frame* expected, struct Frame* result){
    return frame_assertEqual_level(expected, result, 0);
}

void frame_test_showcase_single(struct Frame* fr, int level){
    if(fr == NULL){ return; }
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("%s%s\n", fr->bc, fr->fc);
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("NAME:%s\n", fr->name); 
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("WIDTH:%d\n", fr->ws.width); 
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("HEIGHT:%d\n", fr->ws.height);  
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("ROW:%d\n", fr->row);  
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("COL:%d\n", fr->col);  
    for(int i = 0; i < level; i++){ printf("\t"); }

    /*
       printf("DETAILS:\n");
       for(int i = 0; i < level; i++){ printf("\t"); }
       printf("\tIS_FIELD = %d\n", fr->details.is_field);
       for(int i = 0; i < level; i++){ printf("\t"); }
       printf("\tIS_FOCUS = %d\n", fr->details.is_focus);
       for(int i = 0; i < level; i++){ printf("\t"); }
       printf("\tGL_ROW = %d\n", fr->details.global_row);
       for(int i = 0; i < level; i++){ printf("\t"); }
       printf("\tGL_COL = %d\n", fr->details.global_col);
       for(int i = 0; i < level; i++){ printf("\t"); }
       */

    if(fr->buf != NULL){
        printf("buflen=%lu\n", strlen(fr->buf));
    }else{
        printf("buflen=NULL\n");
    }

    if(fr->fields == NULL){
        printf("LIST IS NULL\n");
        return;
    }
    if(fr->fields->head == NULL){return;}
    struct Node* nptr = fr->fields->head;
    struct Node* stopper = NULL;

    if(nptr != NULL){
        stopper = nptr;
        do{
            if(nptr != NULL){
                if(nptr->value != NULL){
                    frame_test_showcase_single(nptr->value, level + 1);
                }
                nptr = nptr->next;
            }else{return;}
        }while(nptr != stopper);
    }
    printf(RESET);
}

void frame_test_showcase(struct Frame* fr){
    frame_test_showcase_single(fr, 0);
    printf("\n");
    return;
}


int main(){
    /*
       struct Frame* console = frame_console_new_default();
       struct Frame* fr        = frame_new_from_file("./fio.fr");

       frame_push_field(console, fr);
       frame_print(console);
       printf("\n");

       frame_delete(&console);
       */


    //TESTS

    char input;
    do{
        printf("\n>");
        do{
            input = getc(stdin);
        }while (input == '\n');
        printf("%c:%d\n", input, input);
    }while(input != 'q');

    /*
       struct Frame* fr_exp = frame_new("id", get_winsize(20,80),                 0,  0,   BACK_BLUE, FORE_CYAN,    "what");
       struct Frame* frame1 = frame_new("id1", get_winsize(1,20),   5,  10,  BACK_BLACK, FORE_YELLOW, "Name:");
    struct Frame* frame2 = frame_new("id2", get_winsize(1,20),   10, 7,  BACK_BLACK, FORE_YELLOW, "Surname:");
    struct Frame* frame3 = frame_new("id3", get_winsize(1,20),   15, 10,  BACK_BLACK, FORE_YELLOW, "Text:");
    frame_push_field(fr_exp, frame1);
    frame_push_field(fr_exp, frame2);
    frame_push_field(fr_exp, frame3);

    struct Frame* fr_res = frame_new_from_file("./frames/fio.fr");

    //    ring_print(fr_exp->fields);
    //    ring_print(fr_res->fields);
    frame_assertEqual(fr_exp, fr_res);

    frame_test_showcase(fr_exp);
    ERROR("============================");
    frame_test_showcase(fr_res);
    frame_delete(&fr_exp);
    frame_delete(&fr_res);
*/
    return 0;

}
