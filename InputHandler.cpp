#include "InputHandler.h"

// ОПРЕДЕЛЕНИЯ статических переменных (только здесь!)
struct termios InputHandler::originalTermios;
bool InputHandler::initialized = false;

void InputHandler::init() {
    if (initialized) return;
    
    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios newTermios = originalTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    
    initialized = true;
}

char InputHandler::getKey() {
    init();
    char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return ch;
    }
    return 0;
}

void InputHandler::restore() {
    if (initialized) {
        tcsetattr(STDIN_FILENO, TCSANOW, &originalTermios);
    }
}