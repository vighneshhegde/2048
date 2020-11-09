#include"2048.h"

int main(){

    srand(time(NULL));
    
    Grid* g = initgrid();
    printgrid(g);

    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON | ECHO);

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    while (!g->gameover){
        if(getchar() == '\033') { // if the first value is esc
            getchar(); // skip the [
            wprintf(L"\e[1;1H\e[2J"); // clear screen
            switch(getchar()) { // the real value
                case 'A':
                    // code for arrow up
                    setgrid(g,'u');
                    printgrid(g);
                    continue;
                case 'B':
                    // code for arrow down
                    setgrid(g,'d');
                    printgrid(g);
                    continue;
                case 'C':
                    // code for arrow right
                    setgrid(g,'r');
                    printgrid(g);
                    continue;
                case 'D':
                    // code for arrow left
                    setgrid(g,'l');
                    printgrid(g);
                    continue;
            }
        }
        else{
            wprintf(L"Do you really want to quit? (y/n)\n");
            if(getchar() == 'y') break;
            else {
                wprintf(L"\e[1;1H\e[2J"); // clear screen
                printgrid(g);                
            }
        }
    }
    wprintf(L"Game over! You reached %d\n", g->max);

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}