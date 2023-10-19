#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void FlushStdin(void) {
  int ch;
  while(((ch = getchar()) !='\n') && (ch != EOF));
}

void Game(){

    int horizontal, vertical;

    char input;
    for (;;) {
        system("/bin/stty raw");
        input = tolower(getchar());
        if(input == 'w') break;
        system("/bin/stty cooked");
        system("clear");
    }

    for(vertical = 0;vertical < 20; vertical++)
    {
        printf("�");
        for(horizontal = 0; horizontal < 40; horizontal++)
        {
            if(vertical == 0 || vertical == 19) printf("�");
            else printf(" ");
        }
        
        printf("�");
        printf("\n");
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