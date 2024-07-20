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
    list->tail = new_node;
    new_node->prev = list->tail;
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
