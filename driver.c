#include"2048.h"

int main(){

    srand(time(NULL));
    
    Grid* g = initgrid();

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

    //initscreen();
    printgrid(g);

    while (!g->gameover){
        char t = getchar();
        if(t== '\033') { // if the first value is esc
            getchar(); // skip the [
            clrscr();
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
        else if (t == 'u'){
            if(g->isundone == 0){
                g->isundone = 1;
                undogrid(g);
                wprintf(L"Move undone.\n");
            }
            else{
                wprintf(L"Sorry, can't undo more than once.\n");
            }
        }

        else{
            wprintf(L"Do you really want to quit? (y/n)\n");
            if(getchar() == 'y') break;
            else {
                clrscr();
                printgrid(g);                
            }
        }
    }
    wprintf(L""BOLD RED"Game over!"RESET" You reached "YEL"%d\n", g->max);

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
