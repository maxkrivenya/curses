#include "./headers/frame.h"


int frame_assertEqual(struct Frame* expected, struct Frame* result){
    if(expected->name == NULL){
        printf("\n{\n");
    }else{
        printf("\n{%s\n", expected->name);
    }
    int test_passed = 1;
    int same = 1;

    if(expected->field == NULL){
        if(result->field != NULL){
            ERROR("FIELDS ISNT NULL");
            test_passed = 0;
        }
    }else{
        if(result->field == NULL){
            ERROR("FIELDS IS NULL");
            test_passed = 0;
            
        }else{
            if(expected->field->head == NULL){
                if(result->field->head != NULL){
                    ERROR("FIELDS ISNT EMPTY");
                    test_passed = 0;
                }
            }else{
                struct Node* stopper1 = expected->field->head;
                struct Node* stopper2 = result->field->head;
                struct Node* n1 = stopper1;
                struct Node* n2 = stopper2;
                do{
                    if(!frame_assertEqual(n1->value, n2->value)){
                        ERROR("FIELDS IS DIFFERENT!");
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
            ERROR("NAME ISNT NULL");
            printf("result->buf:%s\n", result->buf);
            test_passed = 0;
        }
    }else{
        if(result->buf == NULL){
            ERROR("NAME IS NULL");
            test_passed = 0;
        }
        if(strlen(expected->buf) != strlen(result->buf)){
            ERROR("NAMES ARE DIFFERENT LENGTHS");
            printf("%lu:%lu\t%s:%s\n", strlen(expected->buf), strlen(result->buf),  expected->buf, result->buf);
            test_passed = 0;
        }
        for(int i = 0; i < strlen(expected->buf); i++){
            if(expected->buf[i] != result->buf[i]){
                ERROR("NAMES ARE DIFFERENT");
                printf("%d, '%s':'%s'\n", i, expected->buf, result->buf);
                test_passed = 0;
            }
        }
    }

    if(expected->name == NULL){
        if(result->name != NULL){
            ERROR("NAME ISNT NULL");
            printf("result->name:%s\n", result->name);
            test_passed = 0;
        }
    }else{
        if(result->name == NULL){
            ERROR("NAME IS NULL");
            test_passed = 0;
        }
        if(strlen(expected->name) != strlen(result->name)){
            ERROR("NAMES ARE DIFFERENT LENGTHS");
            printf("%lu:%lu\t%s:%s\n", strlen(expected->name), strlen(result->name),  expected->name, result->name);
            test_passed = 0;
        }
        for(int i = 0; i < strlen(expected->name); i++){
            if(expected->name[i] != result->name[i]){
                ERROR("NAMES ARE DIFFERENT");
                printf("%d, '%s':'%s'\n", i, expected->name, result->name);
                test_passed = 0;
            }
        }
    }

    if(expected->fc != result->fc){
        ERROR("FORECOLORS ARE DIFFERENT");

        printf("%s%sEXPECTED%s\n", expected->bc, expected->fc, RESET);
        printf("%s%sRESULT%s\n", result->bc, result->fc, RESET);
        printf("%lu:%lu\n", *(long*)expected->fc ,*(long*)result->fc);

        test_passed = 0;
    }

    if(expected->bc != result->bc){
        ERROR("BACKCOLORS ARE DIFFERENT");

        printf("%s%sEXPECTED%s\n", expected->bc, expected->fc, RESET);
        printf("%s%sRESULT%s\n", result->bc, result->fc, RESET);
        printf("%lu:%lu\n", *(long*)expected->bc ,*(long*)result->bc);

        test_passed = 0;
    }

    if(expected->bc != result->bc){
        ERROR("BACKCOLORS ARE DIFFERENT");

        printf("%s%sEXPECTED%s\n", expected->bc, expected->fc, RESET);
        printf("%s%sRESULT%s\n", result->bc, result->fc, RESET);
        printf("%lu:%lu\n", *(long*)expected->bc ,*(long*)result->bc);

        test_passed = 0;
    }

    if(expected->ws.width != result->ws.width){
        ERROR("WIDTH IS DIFFERENT");
        test_passed = 0;
    }

    if(expected->ws.height != result->ws.height){
        ERROR("HEIGHT IS DIFFERENT");
        test_passed = 0;
    }

    if(expected->row != result->row){
        ERROR("ROW IS DIFFERENT");
        test_passed = 0;
    }

    if(expected->col != result->col){
        ERROR("COL IS DIFFERENT");
        test_passed = 0;
    }

    if(expected->details.is_field != result->details.is_field){
        ERROR("IS_FIELD IS DIFFERENT");
        test_passed = 0;
    }

    if(expected->details.is_focus != result->details.is_focus){
        ERROR("IS_FOCUS IS DIFFERENT");
        test_passed = 0;
    }

    if(expected->details.global_col != result->details.global_col){
        ERROR("GLOBAL_COL IS DIFFERENT");
        printf("%d:%d\n", expected->details.global_col, result->details.global_col);
        test_passed = 0;
    }

    if(expected->details.global_row != result->details.global_row){
        ERROR("GLOBAL_ROW IS DIFFERENT");
        printf("%d:%d\n", expected->details.global_row, result->details.global_row);
        test_passed = 0;
    }

    if(test_passed){
        SUCCESS("TEST PASSED!");
    }else{
        ERROR("TEST FAILED!");
    }
    printf("\n}\n");
    
    return test_passed;
}

void frame_test_showcase_single(struct Frame* fr, int level){
    if(fr == NULL){ return; }
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("%s%s\n", fr->bc, fr->fc);
    if(fr->name != NULL){
    for(int i = 0; i < level; i++){ printf("\t"); }
    printf("NAME:%s\n", fr->name); 
    }
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

    if(fr->field == NULL){
        printf("LIST IS NULL\n");
        return;
    }
    if(fr->field->head == NULL){return;}
    struct Node* nptr = fr->field->head;
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
    
    frame_field_push(console, fr);
    frame_print(console);
    printf("\n");
    
    frame_delete(&console);
*/


    //TESTS
    
    struct Frame* fr_exp = frame_new(get_winsize(20,80),                 0,  0,   BACK_BLUE, FORE_CYAN,    "what");
    struct Frame* frame1 = frame_new(get_winsize(1,20),   5,  10,  BACK_BLACK, FORE_YELLOW, "Name:");
    struct Frame* frame2 = frame_new(get_winsize(1,20),   10, 7,  BACK_BLACK, FORE_YELLOW, "Surname:");
    struct Frame* frame3 = frame_new(get_winsize(1,20),   15, 10,  BACK_BLACK, FORE_YELLOW, "Text:");
    frame_field_push(fr_exp, frame1);
    frame_field_push(fr_exp, frame2);
    frame_field_push(fr_exp, frame3);

    struct Frame* fr_res = frame_new_from_file("./frames/fio.fr");

//    ring_print(fr_exp->field);
//    ring_print(fr_res->field);
    frame_assertEqual(fr_exp, fr_res);
    frame_test_showcase(fr_exp);
    ERROR("============================");
    frame_test_showcase(fr_res);

    frame_delete(&fr_exp);
    frame_delete(&fr_res);

    return 0;

}
