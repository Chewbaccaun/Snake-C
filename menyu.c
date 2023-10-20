#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define horizontal 60
#define vertical 20

void FlushStdin(void) {
  int ch;
  while(((ch = getchar()) !='\n') && (ch != EOF));
}

void ClearMatrix(int map[vertical][horizontal]) {
    for(int cont = 0;cont < vertical; cont++) {
        for(int cont2 = 0; cont2 < horizontal; cont2++) map[cont][cont2] = 32;
    }
}

void PrintMap(int map[vertical][horizontal], int l, int r, int u, int d) {
    for(int cont = 0;cont < vertical; cont++)
    {
        for(int cont2 = 0; cont2 < horizontal; cont2++)
        {
            if(l == 1 && map[cont][cont2] == '@'){ 
                map[cont][cont2 - 1] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                l = 0;
                break;
            }
            else if(r == 1 && map[cont][cont2] == '@'){ 
                map[cont][cont2 + 1] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                r = 0;
                break;
            }
            else if(u == 1 && map[cont][cont2] == '@'){ 
                map[cont - 1][cont2] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                u = 0;
                break;
            }
            else if(d == 1 && map[cont][cont2] == '@'){ 
                map[cont + 1][cont2] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                d = 0;
                break;
            }
            if(l == 0 && r == 0 && u == 0 && d == 0) break;
        }

    }

    for(int cont = 0;cont < vertical; cont++)
    {
        for(int cont2 = 0; cont2 < horizontal; cont2++)
        {
            if(cont == 0 || cont == vertical - 1) map[cont][cont2] = 61;//Equals sign
            else if(cont2 == 0 || cont2 == horizontal - 1) map[cont][cont2] = 124;//Vertical Line 
            else if(map[cont][cont2] != '@') map[cont][cont2] = 32;//Space
            printf("%c", map[cont][cont2]);
        }
        printf("\n");
    }

}

void Game(){
    int map[vertical][horizontal];
    int cont, cont2;
    
    
    ClearMatrix(map);
    map[vertical/2][horizontal/2] = '@';

    /*char input; //Need to Fix
    for (;;) {
        system("/bin/stty raw");
        input = tolower(getchar());
        if(input == 'w') break;
        system("/bin/stty cooked");
    }*/


    //Arcaic Uga buga Movement
    int l, r, u, d, input;
    for(;;){
        l = 0, r = 0, u = 0, d = 0;
        FlushStdin();
        scanf("%c", &input);
        input = tolower(input);
        if(input == 119) u++;
        if(input == 115) d++; 
        if(input == 97) l++;
        if(input == 100) r++;
        system("clear");
        PrintMap(map, l, r, u, d);
    }
}

int main(){

    char op;
    printf("Snake Game\n\n");
    printf("2. Start the Game\n");
    printf("1. Credits\n");
    printf("0. Exit\n\n");

    op = getchar();

    if(op == '0'){
    return 0;
    }

    else if(op == '1'){
        printf("Gustavo Silva.");
    }

    else if(op == '2'){
        system("clear");
        Game();
    }

    return 0;
}