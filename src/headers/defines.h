#ifndef __defines_h_
#define __defines_h_
#include "winsize.h"


#define FORE_RED     "\033[31m"
#define FORE_GREEN   "\033[32m"
#define FORE_YELLOW  "\033[33m"
#define FORE_BLUE    "\033[34m"
#define FORE_MAGENTA "\033[35m"
#define FORE_CYAN    "\033[36m"
#define RESET        "\033[0m"

#define BACK_BLACK  "\033[40m"
#define BACK_RED "\033[41m"
#define BACK_GREEN "\033[42m"
#define BACK_YELLOW "\033[43m"
#define BACK_BLUE "\033[44m"
#define BACK_MAGENTA "\033[45m"
#define BACK_CYAN "\033[46m"
#define BACK_WHITE "\033[47m"

#ifdef linux
#define WALL  "│"
#define FLOOR "─"
#define TOP_LEFT "┌"
#define TOP_RIGHT "┐"
#define BOTTOM_RIGHT "┘"
#define BOTTOM_LEFT "└"
#define RIGHT_WALL_SPLIT "┤"
#define LEFT_WALL_SPLIT "├"
#define BOTTOM_SPLIT "┴"
#define TOP_SPLIT "┬"
#define CROSS "┼"
#endif
#ifdef _WIN32
#define WALL  "|"
#define FLOOR "-"
#define TOP_LEFT "+"
#define TOP_RIGHT "+"
#define BOTTOM_RIGHT "+"
#define BOTTOM_LEFT "+"
#define RIGHT_WALL_SPLIT "+"
#define LEFT_WALL_SPLIT "+"
#define BOTTOM_SPLIT "+"
#define TOP_SPLIT "+"
#define CROSS "+"
#endif
#define CHUNK 4
#define WORDLEN_MAX 32
#define STRLEN_MAX 128

void ERROR_LEVEL(char* s, int level);
void SUCCESS_LEVEL(char* s, int level);
#ifdef linux
void ERROR(char* s);
#endif
void SUCCESS(char* s);
#endif
