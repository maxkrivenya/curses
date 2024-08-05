#include "./headers/ring.h"
/*===============RING====================*/

struct Ring* ring_new(){
    struct Ring* ring = (struct Ring*)calloc(1, sizeof(struct Ring));
    ring->head = NULL;
    return ring;
}

void ring_push(struct Ring* ring, struct Node* new_node){
    if(ring == NULL || new_node == NULL){ return; }
    if(ring->head == NULL){ 
        ring->head = new_node;
        new_node->prev = new_node;
        new_node->next = new_node;
        return;
    }
    if(ring->head->next == ring->head){
        ring->head->next = new_node;
        ring->head->prev = new_node;
        new_node->prev = ring->head;
        new_node->next = ring->head;
        return;
    }
    new_node->prev = ring->head->prev;
    new_node->next = ring->head;
    ring->head->prev->next = new_node;
    ring->head->prev = new_node;
    return;
}

struct Node* ring_pop(struct Ring* ring){
    if(ring == NULL){ return NULL; }
    if(ring->head == NULL){ return NULL; }
    struct Node* nptr = ring->head;
    if(ring->head->next == ring->head) { 
        ring->head = NULL;
        return nptr;
    }
    ring->head = ring->head->next;
    ring->head->prev = ring->head->prev->prev;
    ring->head->prev->next = ring->head;

    return nptr;
}

void ring_next(struct Ring *ring){
    ring->head = ring->head->next;
}

void ring_free(struct Ring* ring){
    if(ring == NULL) { return; }
    if(ring->head == NULL){ return; }

    struct Node* nptr = ring->head->next;
    struct Node* next;
    struct Node* stopper = ring->head;
    if(stopper == nptr){
        free(nptr);
        free(ring);
        return;
    }

    do{
        next = nptr->next;
        node_delete(nptr);
        nptr = next;
    }while(nptr != stopper);
    node_delete(nptr);
    free(ring);
    return;
}

