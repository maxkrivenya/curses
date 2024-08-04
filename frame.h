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
    struct Ring* field;
    struct List* frames;
};

#define STRLEN_MAX 128
#define WORDLEN_MAX 32

/*----pretty stuff-----------*/
void frame_print_corners(struct Frame* fr);
void frame_print_walls(struct Frame* fr);
void frame_print_floors(struct Frame* fr);
void frame_print_name(struct Frame* fr);

/*----constructors-----------*/
struct Frame* frame_new(struct WinSize ws, int rows, int cols, const char* bc, const char* fc, char* frame_name);
struct Frame* frame_new_default(struct WinSize ws, int rows, int cols);
struct Frame* frame_new_from_file(char* src);

/*----consoles-----------*/
struct Frame* frame_console_new(const char* bc, const char* fc, char* name);
struct Frame* frame_console_new_no_name(const char* bc, const char* f);
struct Frame* frame_console_new_default();

void frame_delete(struct Frame** frame);
void frame_print(struct Frame* fr);
void frame_field_push(struct Frame* dest, struct Frame* fr);

struct Node* frame_get_first_field_node(struct Ring* ring);

struct WinSize cursor_get(struct Frame* fr, struct Frame* x);
