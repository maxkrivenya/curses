#include "headers.h"

struct WinSize{
    int height;
    int width;

};

struct WinSize get_console_size();
struct WinSize get_winsize(int rows, int cols);
