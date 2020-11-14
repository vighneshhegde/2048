#include<time.h>
#include<stdio.h>
#include<wchar.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define BOLD  "\x1B[1m"
//90 to 97 is also fair game, brighter version of these colours.

#define LOOP(n) for(int ii = 0; ii < n; ++ ii)
#define clrscr() wprintf(L"\e[1;1H\e[2J") // clear screen


typedef struct grid{
    int* v; //value
    int* ov; //old value
    int* z; //zero indices
    int i; //just a bookkeeping variable
    int size; //dimensions, size x size
    int max; //max value at any given state
    int score; //merge + change additions
    int gameover; //is 0 while the game is running
    int isundone; //is 1 if undo already granted
    wchar_t hint; //char to store hint
} Grid;

Grid* initgrid();
int initscreen();

//print helpers
void centerText(char *text, char* colour, int fieldWidth);
void printN(wchar_t ch, int n);
void print_int(int x, int w);
void printgrid(Grid* g);
void set_hint(Grid*g, char c);

char check_for_moves(Grid* g);
void setgrid(Grid* g, char com);
void undogrid(Grid* g);
