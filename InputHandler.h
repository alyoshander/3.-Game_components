#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class InputHandler {
private:
    static struct termios originalTermios;  // только ОБЪЯВЛЕНИЕ
    static bool initialized;                 // только ОБЪЯВЛЕНИЕ
    
    static void init();
    
public:
    static char getKey();
    static void restore();
};

#endif