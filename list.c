#include "list.h"

struct List* new_list(){
    struct List* list = (struct List*)calloc(1, sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void push(struct List* list, struct Node* new_node){
    if(list->head == NULL){
        list->head = new_node;
        list->tail = new_node;
        return;
    }
    if(list->head == list->tail){
        new_node->prev = list->head;
        list->head->next = new_node;
        list->tail = new_node;
        return;
    }

    struct Node* nptr = list->head;
    while(nptr->fr->row < new_node->fr->row){
        if(nptr->next == NULL) { break; }
        nptr = nptr->next;
    }
    while(nptr->fr->row == new_node->fr->row  && nptr->fr->col < new_node->fr->col){
        if(nptr->next == NULL) { break; }
        nptr = nptr->next;
    }

    if(nptr == list->tail){
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
        return;
    }
    if(nptr == list->head){
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
        return;
    }
    new_node->prev = nptr;
    new_node->next = nptr->next;
    nptr->next->prev = new_node;
    nptr->next = new_node;
    return;
}

void pop(struct List* list, struct Frame* fr){
    if(fr == NULL) { return; }
    if(list == NULL){ return; }
    if(list->head == NULL){ return; }
    struct Node* nptr = list->head;
    do{
        if(nptr->fr == fr){
            if(nptr->prev == NULL && nptr->next == NULL){
                delete_node(nptr);
                return;
            }
            if(nptr->prev == NULL){
                list->head = list->head->next;
                list->head->prev = NULL;
                delete_node(nptr);
                return;
            }
            if(nptr->next == NULL){
                list->tail = list->tail->prev;
                list->tail->next = NULL;
                delete_node(nptr);
                return;
            }
            nptr->prev->next = nptr->next;
            nptr->next->prev = nptr->prev;
            delete_node(nptr);
            return;
        }
        nptr = nptr->next;
    }while(nptr != NULL);
}

void free_list(struct List* list){
    if(list == NULL){return;}
    struct Node * node = list->head;
    struct Node * next = NULL;
    while(node != NULL){
        next = node->next;
        delete_frame(&node->fr);
        free(node);
        node = next;
    }
    free(list);
}
