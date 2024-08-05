#include "./headers/winsize.h"

struct WinSize get_console_size(){
    struct winsize ws;
    int fd;

    fd = open("/dev/tty", O_RDWR);
    if(fd < 0 || ioctl(fd, TIOCGWINSZ, &ws) < 0) err(8, "/dev/tty");

    struct WinSize size;
    size.height = ws.ws_row;
    size.width = ws.ws_col;

    close(fd);
    return size;
}

struct WinSize get_winsize(int rows, int cols){
    struct WinSize ws = {rows, cols};
    return ws;
}
