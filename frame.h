#include "defines.h"

struct Frame{
    struct WinSize ws;
    char* name;
    char* buf;
    int row;
    int col;
    int is_focus;
    const char* fc;
    const char* bc;
    struct List* field;
};

void corners(struct Frame* fr);
void walls(struct Frame* fr);
void floors(struct Frame* fr);
void name(struct Frame* fr);
struct Frame* new_frame(struct WinSize ws, int rows, int cols, const char* bc, const char* fc, char* frame_name);
struct Frame* new_default_frame(struct WinSize ws, int rows, int cols);
struct Frame* new_console_full(const char* bc, const char* fc, char* name);
struct Frame* new_console_noname(const char* bc, const char* fc, char* name);
struct Frame* new_default_console();
void delete_frame(struct Frame** frame);
void print_frame(struct Frame* fr);
//void render_frame(struct Frame* fr, int lvl);
void render_frame_to_frame(struct Frame* dest, struct Frame* fr, int lvl);
