#include "./headers/winsize.h"

struct WinSize get_console_size(){
    struct WinSize size;

    #ifdef linux
        struct winsize ws;
        int fd;

        fd = open("/dev/tty", O_RDWR);
        if(fd < 0 || ioctl(fd, TIOCGWINSZ, &ws) < 0) err(8, "/dev/tty");


        size.height = ws.ws_row;
        size.width = ws.ws_col;

        close(fd);
    #endif
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        size.height = rows;
        size.width = columns;
    #endif
    return size;
}

struct WinSize get_winsize(int rows, int cols){
    struct WinSize ws = {rows, cols};
    return ws;
}
