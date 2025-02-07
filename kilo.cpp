#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

using namespace std;

struct termios orig_termios;

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

//function enables terminal raw mode by editing terminal flag to turn off ECHO, at exit sets the terminal back to the original state
void enableRawMode(){
    
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); //TCSAFLUSH specifies to change the attributes when all pending output has been written [discards all pending input]
}
int main(){
    enableRawMode();
    char c;
    // read input one byte at a time and put into the character c, exit when q is pressed
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}