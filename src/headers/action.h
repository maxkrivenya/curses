#ifndef __action_h_
#define __action_h_
#include "frame.h"
struct Action{
    char    trigger;
    void    (*action)(struct Frame*, void*);
    void*   parameters;
    struct Frame*   parent;
};

struct Action* action_new(char trigger, void (*func_ptr)(struct Frame*, void*), void* params);
void action_delete(struct Action* action);
#endif
