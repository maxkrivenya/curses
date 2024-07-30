#include "defines.h"

struct Details{
    int is_focus;
    int is_field;
    int global_row;
    int global_col;
};

struct Frame{
    struct WinSize ws;
    struct Details details;
    char* name;
    char* buf;
    int row;
    int col;
    const char* fc;
    const char* bc;
    struct List* field;
    struct List* frames;
};

/*----pretty stuff-----------*/
void corners(struct Frame* fr);
void walls(struct Frame* fr);
void floors(struct Frame* fr);
void name(struct Frame* fr);

/*----constructors-----------*/
struct Frame* new_frame(struct WinSize ws, int rows, int cols, const char* bc, const char* fc, char* frame_name);
struct Frame* new_default_frame(struct WinSize ws, int rows, int cols);
struct Frame* new_console_full(const char* bc, const char* fc, char* name);
struct Frame* new_console_noname(const char* bc, const char* fc, char* name);
struct Frame* new_default_console();
void delete_frame(struct Frame** frame);

void push_frame(struct Frame* dest, struct Frame* fr);
void print_frame(struct Frame* fr);
struct Node* get_first_field(struct List* list);

struct WinSize get_cursor(struct Frame* fr, struct Frame* x);
