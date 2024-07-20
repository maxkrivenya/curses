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
    while(nptr->row < new_node->row){
        if(nptr->next == NULL) { break; }
        nptr = nptr->next;
    }
    while(nptr->row == new_node->row  && nptr->col < new_node->col){
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

void free_list(struct List* list){
    if(list == NULL){return;}
    struct Node * node = list->head;
    struct Node * next = NULL;
    while(node != NULL){
        next = node->next;
        free(node);
        node = next;
    }
    free(list);
}
