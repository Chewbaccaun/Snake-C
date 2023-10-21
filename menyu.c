#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#define horizontal 100
#define vertical 36

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

int ResetLife(int map[vertical][horizontal], int life){
    map[vertical/2][horizontal/2] = '@';
    life--;
    return life;
}

void PrintInterface(int map[vertical][horizontal], int life) {

    printf("Life: %d\n\n", life);
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

int Movement(int map[vertical][horizontal], int left, int right, int up, int down, int life) {
    for(int cont = 0;cont < vertical; cont++) {
        for(int cont2 = 0; cont2 < horizontal; cont2++) {
            if(left == 1 && map[cont][cont2] == '@') { 
                map[cont][cont2 - 1] = 64; //64 = @
                if(map[cont][0] == '@') life = ResetLife(map, life);
                map[cont][cont2] = 32; //Space
                left = 0;
                break;
            }
            else if(right == 1 && map[cont][cont2] == '@') { 
                map[cont][cont2 + 1] = 64; //64 = @
                if(map[cont][horizontal - 1] == '@' ) life = ResetLife(map, life);
                map[cont][cont2] = 32; //Space
                right = 0;
                break;
            }
            else if(up == 1 && map[cont][cont2] == '@') { 
                map[cont - 1][cont2] = 64; //64 = @
                if(map[0][cont2] == '@') life = ResetLife(map, life);
                map[cont][cont2] = 32; //Space
                up = 0;
                break;
            }
            else if(down == 1 && map[cont][cont2] == '@') { 
                map[cont + 1][cont2] = 64; //64 = @
                if(map[vertical - 1][cont2] == '@') life = ResetLife(map, life);
                map[cont][cont2] = 32; //Space
                down = 0;
                break;
            }
            if(left == 0 && right == 0 && up == 0 && down == 0) break;
        }
    }
    PrintInterface(map, life);
    return life;
}

void Game(){
    int map[vertical][horizontal];
    int cont, cont2;
    int life = 4;

    ClearMatrix(map);
    life = ResetLife(map, life);

    //Need to Improve
    for (int left = 0, right = 0, up = 0, down = 0, input = 0;;) {
        system("clear");
        life = Movement(map, left, right, up, down, life);
        if(life == 0) break;
        left = 0, right = 0, up = 0, down = 0, input = 0;
        input = tolower(getch());
        if(input == 119) up++;
        if(input == 115) down++; 
        if(input == 97) left++;
        if(input == 100) right++;
        if(life == 0) exit;
    }
    system("clear");
    printf("Game Over.\n\n");
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