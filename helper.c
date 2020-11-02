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

void exit_game(){
    wprintf(L"Game over!\n");
    ungetc('q',stdin); //write something better
    return;
}


void printgrid(Grid* g){
    setlocale(LC_CTYPE, "");
    wchar_t star = 0x2605;
    g->i=0;
    wprintf(L"\e[1;1H\e[2J");
    //wprintf()
    //wprintf(L"%lc%.*lc%lc\n", 0x250c,5,0x2500,0x252c);
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
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
           ; 
        }
    }
}

void print_hint(char c){
    switch(c){
        case 'u':
           wprintf(L"Hint: Try up\n"); 
           break;
        case 'd':
           wprintf(L"Hint: Try down\n"); 
           break;
        case 'r':
           wprintf(L"Hint: Try right\n"); 
           break;
        case 'l':
           wprintf(L"Hint: Try left\n"); 
           break;
        default:
           break;
    }
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
    Grid* g = malloc(sizeof(struct grid));
    g->v = malloc(sizeof(int)*16);
    g->z = malloc(sizeof(int)*16);
    g->i = 0;
    g->v[0]=2;
    for(int i=1;i<16;i++){
        g->v[i]=0;
    }
    return g;
}

void setgrid(Grid* g, char com){
    //com can be 'u','d','l', or 'r'
    //shift non-zero elements according to the given command
    int change=1;
    switch(com){
        case 'u':
            while(change){
                change = 0;
                for(int i=4;i<16;i++){
                    if(g->v[i-4]==0&&g->v[i]!=0){//shift
                        g->v[i-4]=g->v[i];
                        g->v[i]=0;
                        change=1;
                    }
                    else if(g->v[i-4]==g->v[i]&&g->v[i]!=0){//merge
                        g->v[i-4]+=g->v[i];
                        g->v[i]=0;
                        //change=1;
                    }
                }
            }
            break;
        case 'd':
            while(change){
                change = 0;
                for(int i=11;i>=0;i--){
                    if(g->v[i+4]==0&&g->v[i]!=0){//shift
                        g->v[i+4]=g->v[i];
                        g->v[i]=0;
                        change=1;
                    }
                    else if(g->v[i+4]==g->v[i]&&g->v[i]!=0){//merge
                        g->v[i+4]+=g->v[i];
                        g->v[i]=0;
                        //change=1;
                    }
                }
            }
            break;
        case 'l':
            while(change){
                change = 0;
                int ind[12] = {1,2,3,5,6,7,9,10,11,13,14,15};
                for(int i=0;i<12;i++){
                    if(g->v[ind[i]-1]==0&&g->v[ind[i]]!=0){//shift
                        g->v[ind[i]-1]=g->v[ind[i]];
                        g->v[ind[i]]=0;
                        change=1;
                    }
                    else if(g->v[ind[i]-1]==g->v[ind[i]]&&g->v[ind[i]]!=0){//merge
                        g->v[ind[i]-1]+=g->v[ind[i]];
                        g->v[ind[i]]=0;
                        //change=1;
                    }
                }
            }
            break;
        case 'r':
            while(change){
                change = 0;
                //wprintf(L"1");
                int ind[12] = {0,1,2,4,5,6,8,9,10,12,13,14};
                for(int i=11;i>=0;i--){
                    if(g->v[ind[i]+1]==0&&g->v[ind[i]]!=0){//shift
                        g->v[ind[i]+1]=g->v[ind[i]];
                        g->v[ind[i]]=0;
                        change=1;
                    }
                    else if(g->v[ind[i]+1]==g->v[ind[i]]&&g->v[ind[i]]!=0){//merge
                        g->v[ind[i]+1]+=g->v[ind[i]];
                        g->v[ind[i]]=0;
                        //change=1;
                    }
                }
            }
            break;
        default:
            break;

    }
    //randomly add a new 2 or a 4
    int randn = 0;
    if(rand()%10==0) randn=4; //10% chance of 4 
    else if(rand()%10<5) randn=2;  //45% chance of 2

    int nz = 0;
    for(int i=0;i<16;i++){
        if(g->v[i]==0) g->z[nz++]=i;
    }

    //if no more zeros left, end the game
    if(nz==0){
        char chk = check_for_moves(g);
        if(chk =='x'){
            exit_game();
        }
        else{
           print_hint(chk); 
        }
    }
    else
        g->v[g->z[rand()%nz]] = randn;

}
