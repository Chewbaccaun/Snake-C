#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#define horizontal 120
#define vertical 40

void FlushStdin(void) {
  int ch;
  while(((ch = getchar()) !='\n') && (ch != EOF));
}

char getch() { //https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
} 

void ClearMatrix(int map[vertical][horizontal]) {
    for(int cont = 0;cont < vertical; cont++) {
        for(int cont2 = 0; cont2 < horizontal; cont2++) map[cont][cont2] = 32;
    }
}

void PrintMap(int map[vertical][horizontal]) {
    for(int cont = 0;cont < vertical; cont++) {
        for(int cont2 = 0; cont2 < horizontal; cont2++) {
            if(cont == 0 || cont == vertical - 1) map[cont][cont2] = 61;//Equals sign
            else if(cont2 == 0 || cont2 == horizontal - 1) map[cont][cont2] = 124;//Vertical Line 
            else if(map[cont][cont2] != '@') map[cont][cont2] = 32;//Space
            printf("%c", map[cont][cont2]);
        }
        printf("\n");
    }
}

void Movement(int map[vertical][horizontal], int l, int r, int u, int d) {
    for(int cont = 0;cont < vertical; cont++) {
        for(int cont2 = 0; cont2 < horizontal; cont2++) {
            if(l == 1 && map[cont][cont2] == '@' && cont2 - 1 > 0) { 
                map[cont][cont2 - 1] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                l = 0;
                break;
            }
            else if(r == 1 && map[cont][cont2] == '@' && cont2 + 1 < horizontal - 1) { 
                map[cont][cont2 + 1] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                r = 0;
                break;
            }
            else if(u == 1 && map[cont][cont2] == '@' && cont - 1 > 0) { 
                map[cont - 1][cont2] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                u = 0;
                break;
            }
            else if(d == 1 && map[cont][cont2] == '@' && cont + 1 < vertical - 1) { 
                map[cont + 1][cont2] = 64; //64 = @
                map[cont][cont2] = 32; //Space
                d = 0;
                break;
            }
            if(l == 0 && r == 0 && u == 0 && d == 0) break;
        }
    }
    PrintMap(map);
}

void Game(){
    int map[vertical][horizontal];
    int cont, cont2;
    
    ClearMatrix(map);
    map[vertical/2][horizontal/2] = '@';

    //Need to Improve
    int l, r, u, d, input;
    for (l = 0, r = 0, u = 0, d = 0;;) {
        system("clear");
        Movement(map, l, r, u, d);
        l = 0, r = 0, u = 0, d = 0, input = 0;
        input = tolower(getch());
        if(input == 119) u++;
        if(input == 115) d++; 
        if(input == 97) l++;
        if(input == 100) r++;
    }
}

int main(){

    char op;
    printf("Snake Game\n\n2. Start the Game\n1. Credits\n0. Exit\n\n");

    op = getchar();
    if(op == '0') return 0;
    else if(op == '1') {
        system("clear");
        printf("Gustavo Silva.\nStack Overflow Geniuses.\n\n");
    }
    else if(op == '2') {
        system("clear");
        Game();
    }
    return 0;
}