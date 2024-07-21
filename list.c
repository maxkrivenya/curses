#include "list.h"

struct List* new_list(){
    struct List* list = (struct List*)calloc(1, sizeof(struct List));
    list->head = NULL;
    return list;
}

void push(struct List* list, struct Node* new_node){
    if(list->head == NULL){
        list->head = new_node;
        return;
    }
    if(list->head->next == NULL){
        new_node->prev = list->head;
        new_node->next = list->head;
        list->head->next = new_node;
        list->head->prev = new_node;
        //list->tail = new_node;
        return;
    }

    list->head->prev->next = new_node;
    new_node->prev = list->head->prev;
    new_node->next = list->head;
    list->head->prev = new_node;
    return;
}

void pop(struct List* list){
    if(list == NULL){ return; }
    if(list->head == NULL){ return; }
    list->head = list->head->next;
}

void free_list(struct List* list){
    if(list == NULL){return;}
    if(list->head == NULL){ return; }
    struct Node * node = list->head;
    struct Node* stopper = list->head->prev;

    struct Node * next = NULL;
    while(node != stopper){
        next = node->next;
        delete_frame(&node->fr);
        free(node);
        node = next;
    }
    delete_frame(&stopper->fr);
    free(stopper);
    free(list);
}
