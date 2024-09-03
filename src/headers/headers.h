#ifndef __headers_h_
#define __headers_h_
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


#include <string.h>
#include <ctype.h>
#include <math.h>

#ifdef linux
      #include <err.h>
      #include <unistd.h>
      #include <termios.h>
      #include <sys/ioctl.h>
      #include <sys/stat.h>
#endif

#ifdef _WIN32
	#include <windows.h>
#endif

#endif
