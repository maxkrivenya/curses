#include "./headers/list.h"

struct List* list_new(){
    struct List* list = (struct List*)calloc(1, sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_push_tail(struct List* list, struct Node* new_node){
    if(list == NULL){ list = list_new(); }
    if(list->head == NULL){
        list->head = new_node;
        list->tail = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
        return;
    }
    new_node->prev      = list->tail;
    new_node->next      = NULL;
    list->tail->next    = new_node;
    list->tail          = new_node;
    return;
}

// NULL prev<-[1]-><-[2]->next NULL = NULL prev<-[2]->next NULL 
struct Node* list_pop_head(struct List* list){
    if(list == NULL){ return NULL; }
    if(list->head == NULL){ return NULL; }
    struct Node* nptr = list->head;
    if(list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
        return nptr;
    }
    list->head = list->head->next;
    list->head->prev = NULL;
    return nptr;
}

// NULL prev<-[1]-><-[2]->next NULL = NULL prev<-[2]->next NULL 
struct Node* list_pop_tail(struct List* list){
    if(list == NULL){ return NULL; }
    if(list->head == NULL){ return NULL; }
    struct Node* nptr = list->tail;
    if(list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
        return nptr;
    }
    list->tail = list->tail->prev;
    list->tail->prev = NULL;
    return nptr;
}

void list_free(struct List* list){
    if(list == NULL){return;}
    if(list->head == NULL){ return; }

    struct Node * nptr = list->head;
    struct Node * next = NULL;

    do{
        next = nptr->next;
        node_delete(nptr);
        nptr = next;
    }while(nptr != NULL);

    free(list);
}

