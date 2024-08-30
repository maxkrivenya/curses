#include "./headers/action.h"

struct Action* action_new(char trigger, void (*func_ptr)(struct Frame*, void*), void* params){
   struct Action* action = (struct Action*)calloc(1, sizeof(struct Action));

   action->trigger = trigger;
   if(func_ptr == NULL){return action;}
   action->action = func_ptr;
   action->parameters = params;

   return action;
}

void action_delete(struct Action* action){
    if(action != NULL){
        free(action);
    }
}
