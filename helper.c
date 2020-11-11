#include"2048.h"

void centerText(char *text, char* colour, int fieldWidth) {
    int padlen = (fieldWidth - strlen(text)) / 2;
    int padrem = (fieldWidth - strlen(text)) % 2;
    wprintf(L"%s%*s%s%*s"RESET, colour, padlen+padrem, "", text, padlen, "");
} 

void printN(wchar_t ch, int n){
    while(n-->0){
        wprintf(L"%lc",ch);
    }
}

void print_int(int x, int w){
    if(x==0){
        centerText(" ",RESET,w);
    }
    else{
        int length = snprintf( NULL, 0, "%d", x );
        char* str = malloc( length + 1 );
        snprintf(str, length + 1, "%d", x );

        switch(x){
            case 2048:
                centerText(str,YEL,w); 
                break;
            case 1024:
                centerText(str,RED,w); 
                break;
            case 512:
                centerText(str,RED,w); 
                break;
            case 256:
                centerText(str,MAG,w); 
                break;
            case 128:
                centerText(str,MAG,w); 
                break;
            case 64:
                centerText(str,CYN,w); 
                break;
            case 32:
                centerText(str,CYN,w); 
                break;
            case 16:
                centerText(str,BLU,w); 
                break;
            case 8:
                centerText(str,BLU,w); 
                break;
            default:
                centerText(str,RESET,w); 
                break;
        }
        free(str);
    }
}


void printgrid(Grid* g){
    setlocale(LC_CTYPE, "");
    g->i=0;
    //wprintf(L"%lc%.*lc%lc\n", 0x250c,5,0x2500,0x252c);
    //TODO: print title and score here. Score is sum of all merges so far
    wprintf(L"\t\t  "RED BOLD"2048\n");
    wprintf(L""CYN BOLD"Score:"RESET"\t%d\n",g->score);
    printN(0x250c,1); 
    printN(0x2500,9); 
    LOOP(3){
        printN(0x252c,1); 
        printN(0x2500,9); 
    }
    printN(0x2510,1); 
    wprintf(L"\n");

    LOOP(3){
        printN(0x2502,1); 
        printN(0x0020,9); 
        LOOP(3){
            printN(0x2502,1); 
            printN(0x0020,9); 
        }
        printN(0x2502,1); 
        wprintf(L"\n");

        printN(0x2502,1); 
        printN(0x0020,2); 
        print_int(g->v[g->i++],5);
        printN(0x0020,2); 
        LOOP(3){
            printN(0x2502,1); 
            printN(0x0020,2); 
            print_int(g->v[g->i++],5);
            printN(0x0020,2); 
        }
        printN(0x2502,1); 
        wprintf(L"\n");

        printN(0x2502,1); 
        printN(0x0020,9); 
        LOOP(3){
            printN(0x2502,1); 
            printN(0x0020,9); 
        }
        printN(0x2502,1); 
        wprintf(L"\n");

        printN(0x251c,1); 
        printN(0x2500,9); 
        LOOP(3){
            printN(0x253c,1); 
            printN(0x2500,9); 
        }
        printN(0x2524,1); 
        wprintf(L"\n");
    }
    printN(0x2502,1); 
    printN(0x0020,9); 
    LOOP(3){
        printN(0x2502,1); 
        printN(0x0020,9); 
    }
    printN(0x2502,1); 
    wprintf(L"\n");

    printN(0x2502,1); 
    printN(0x0020,2); 
    print_int(g->v[g->i++],5);
    printN(0x0020,2); 
    LOOP(3){
        printN(0x2502,1); 
        printN(0x0020,2); 
        print_int(g->v[g->i++],5);
        printN(0x0020,2); 
    }
    printN(0x2502,1); 
    wprintf(L"\n");

    printN(0x2502,1); 
    printN(0x0020,9); 
    LOOP(3){
        printN(0x2502,1); 
        printN(0x0020,9); 
    }
    printN(0x2502,1); 
    wprintf(L"\n");


    printN(0x2514,1); 
    printN(0x2500,9); 
    LOOP(3){
        printN(0x2534,1); 
        printN(0x2500,9); 
    }
    printN(0x2518,1); 
    wprintf(L"\n");
    
    if(g->hint!=0){
        wprintf(L"Hint: Try %lc\n",g->hint);
        g->hint = 0;
    }
}

void set_hint(Grid* g, char c){
    wchar_t ch;
    switch(c){
        case 'u':
            ch = 0x2191;
            break;
        case 'd':
            ch = 0x2192;
            break;
        case 'r':
            ch = 0x2193;
            break;
        case 'l':
            ch = 0x2190;
            break;
        default:
            break;
    }
    g->hint = ch;
    //g->hint = malloc(12*sizeof(wchar_t));
    //swprintf(g->hint, 12*sizeof(wchar_t), L"Hint: Try %lc\n",ch); 
}

char check_for_moves(Grid* g){
    for(int i=4;i<16;i++){
        if(g->v[i-4]==g->v[i]&&g->v[i]!=0){//merge
            return 'u';
        }
    }
    for(int i=11;i>=0;i--){
        if(g->v[i+4]==g->v[i]&&g->v[i]!=0){//merge
            return 'd';
        }
    }
    int ind[12] = {1,2,3,5,6,7,9,10,11,13,14,15};
    for(int i=0;i<12;i++){
        if(g->v[ind[i]-1]==g->v[ind[i]]&&g->v[ind[i]]!=0){//merge
            return 'l';
        }
    }
    int rind[12] = {0,1,2,4,5,6,8,9,10,12,13,14};
    for(int i=11;i>=0;i--){
        if(g->v[rind[i]+1]==g->v[rind[i]]&&g->v[rind[i]]!=0){//merge
            return 'r';
        }
    }
    return 'x';
}

Grid* initgrid(){
    int size = 4;
    size = size*size;

    Grid* g = malloc(sizeof(struct grid));
    g->v = malloc(sizeof(int)*size);
    g->ov = malloc(sizeof(int)*size);
    g->z = malloc(sizeof(int)*size);
    g->size = size;
    g->i = 0;
    g->max = 2;
    g->score = 2;
    g->gameover = 0;
    g->isundone = 1;
    g->hint = 0;
    for(int i=0;i<size;i++){
        g->v[i]=0;
    }
    g->v[rand()%size]=2;
    return g;
}

void initscreen(){
    setlocale(LC_CTYPE, "");
    wprintf(L"\e[1;1H\e[2J"); // clear screen
    wprintf(L""BOLD RED"\t\t  2048\n"RESET); 

    wprintf(L"Use arrow keys (%lc %lc %lc %lc ) for controlling the grid",
            0x2190,0x2191,0x2192,0x2193);
    wprintf(L"\n\n\n\t\t\tPress any key to begin...\n");
    getchar();
    wprintf(L"\e[1;1H\e[2J"); // clear screen

}

void setgrid(Grid* g, char com){
    //com can be 'u','d','l', or 'r'
    //shift non-zero elements according to the given command
    int change=0;
    int* temp = malloc(g->size*sizeof(int));//to be freed before this function exits
    memcpy(temp, g->v, g->size*sizeof(int));
    switch(com){
        case 'u':
            {
                for(int i=4;i<16;i++){
                    if(g->v[i-4]==0&&g->v[i]!=0){//shift
                        change = 1;
                        g->v[i-4]=g->v[i];
                        g->v[i]=0;
                        if(i-4>=4)i-=5; //5 to correct for the ++, I should ideally use continue;
                    }
                    else if(g->v[i-4]==g->v[i]&&g->v[i]!=0){//merge & shift
                        change = 1;
                        g->v[i-4]+=g->v[i];
                        g->v[i]=0;
                        g->score += g->v[i-4];
                        for(int j=i;j+4<16;j+=4){
                            g->v[j]=g->v[j+4];
                            g->v[j+4]=0;
                        }
                        if(g->v[i-4] > g->max) g->max=g->v[i-4];
                    }
                }
            }
            break;
        case 'd':
            {
                for(int i=11;i>=0;i--){
                    if(g->v[i+4]==0&&g->v[i]!=0){//shift
                        change = 1;
                        g->v[i+4]=g->v[i];
                        g->v[i]=0;
                        if(i+4<=11)i+=5;
                    }
                    else if(g->v[i+4]==g->v[i]&&g->v[i]!=0){//merge & shift
                        change = 1;
                        g->v[i+4]+=g->v[i];
                        g->v[i]=0;
                        g->score += g->v[i+4];
                        for(int j=i;j-4>=0;j-=4){
                            g->v[j]=g->v[j-4];
                            g->v[j-4]=0;
                        }
                        if(g->v[i+4] > g->max) g->max=g->v[i+4];
                    }
                }
            }
            break;
        case 'l':
            {
                int ind[12] = {1,2,3,5,6,7,9,10,11,13,14,15};
                for(int i=0;i<12;i++){
                    if(g->v[ind[i]-1]==0&&g->v[ind[i]]!=0){//shift
                        change = 1;
                        g->v[ind[i]-1] = g->v[ind[i]];
                        g->v[ind[i]] = 0;
                        if(i-1>=0&&ind[i]%4!=1)i-=2; //-2 to compensate for ++
                    }
                    else if(g->v[ind[i]-1]==g->v[ind[i]]&&g->v[ind[i]]!=0){//merge
                        change = 1;
                        g->v[ind[i]-1]+=g->v[ind[i]];
                        g->v[ind[i]]=0;
                        g->score += g->v[ind[i]-1];
                        for(int j=ind[i];(j+1)%4!=0;j++){
                            g->v[j] = g->v[j+1];
                            g->v[j+1] = 0;
                        }
                        if(g->v[ind[i]-1] > g->max) g->max=g->v[ind[i]-1];
                    }
                }
            }
            break;
        case 'r':
            {
                change = 0;
                //wprintf(L"1");
                int ind[12] = {0,1,2,4,5,6,8,9,10,12,13,14};
                for(int i=11;i>=0;i--){
                    if(g->v[ind[i]+1]==0&&g->v[ind[i]]!=0){//shift
                        change = 1;
                        g->v[ind[i]+1] = g->v[ind[i]];
                        g->v[ind[i]] = 0;
                        if(i+1<=11 && ind[i]%4!=2)i+=2;
                    }
                    else if(g->v[ind[i]+1]==g->v[ind[i]]&&g->v[ind[i]]!=0){//merge
                        change = 1;
                        g->v[ind[i]+1]+=g->v[ind[i]];
                        g->v[ind[i]]=0;
                        g->score += g->v[ind[i]+1];
                        for(int j=ind[i];j%4!=0;j--){
                            g->v[j] = g->v[j-1];
                            g->v[j-1] = 0;
                        }
                        if(g->v[ind[i]+1] > g->max) g->max=g->v[ind[i]+1];
                    }
                }
            }
            break;
        default:
            break;

    }


    int nz = 0;
    for(int i=0;i<16;i++){
        if(g->v[i]==0) g->z[nz++]=i;
    }
    
    //if no more zeros left, end the game
    if(nz==0){
        char chk = check_for_moves(g);
        if(chk =='x'){
           g->gameover = 1;
        }
        else if(change==0){
           set_hint(g, chk); 
        }
    }
    else if(change==1){
        //randomly add a new 2 or a 4 if the grid changed
        int randn = 2;
        if(rand()%10==0) randn=4; //10% chance of 4, 90% chance of 2, no chance of 0
        g->v[g->z[rand()%nz]] = randn;
        g->score += randn;
    }

    if(change==1){
        free(g->ov);
        g->ov = temp;//the value of grid is stored in this variable
        g->isundone = 0;
    }
    else
        free(temp);

}

void undogrid(Grid* g){
    //if undone once then do nothing
    memcpy(g->v, g->ov, g->size*sizeof(int));
    clrscr();
    printgrid(g);
}
