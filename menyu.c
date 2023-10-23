#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#define horizontal 80
#define vertical 20

int ResetLife(int map[vertical][horizontal], int *life)
{
    map[vertical / 2][horizontal / 2] = '@';
    return *life - 1;
}

int CollisionLeft(int map[vertical][horizontal], int left, int cont, int cont2, int *Life)
{
    map[cont][cont2 - 1] = 64; // 64 = @
    if (map[cont][0] == '@')
    {
        *Life = ResetLife(map, Life);
        map[cont][0] = 124; // Vertical Line
    }
    map[cont][cont2] = 32; // Space
    return left = 0;
}

int CollisionRight(int map[vertical][horizontal], int right, int cont, int cont2, int *Life)
{
    map[cont][cont2 + 1] = 64; // 64 = @
    if (map[cont][horizontal - 1] == '@')
    {
        *Life = ResetLife(map, Life);
        map[cont][horizontal - 1] = 124; // Vertical Line
    }
    map[cont][cont2] = 32; // Space
    return right = 0;
}

int CollisionUp(int map[vertical][horizontal], int up, int cont, int cont2, int *Life)
{
    map[cont - 1][cont2] = 64; // 64 = @
    if (map[0][cont2] == '@')
    {
        *Life = ResetLife(map, Life);
        map[0][cont2] = 61; // Equals sign
    }
    map[cont][cont2] = 32; // Space
    return up = 0;
}

int CollisionDown(int map[vertical][horizontal], int down, int cont, int cont2, int *Life)
{
    map[cont + 1][cont2] = 64; // 64 = @
    if (map[vertical - 1][cont2] == '@')
    {
        *Life = ResetLife(map, Life);
        map[vertical - 1][cont2] = 61; // Equals sign
    }
    map[cont][cont2] = 32; // Space
    return down = 0;
}

void Food(int map[vertical][horizontal])
{ // Implementation Needed
    srand(time(NULL));
    int rand1, rand2;
    rand1 = rand() % vertical - 2;
    rand2 = rand() % horizontal - 2;
    if (map[rand1][rand2] != 64 && rand1 != 0 && rand2 != 0) // 64 = @
        map[rand1][rand2] = '*';
}

void FlushStdin(void)
{
    int ch;
    while (((ch = getchar()) != '\n') && (ch != EOF))
        ;
}

char getch()
{ // https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
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
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

void ResetMatrix(int map[vertical][horizontal])
{
    for (int cont = 0; cont < vertical; cont++)
    {
        for (int cont2 = 0; cont2 < horizontal; cont2++)
        {
            if (cont == 0 || cont == vertical - 1)
                map[cont][cont2] = 61; // Equals sign
            else if (cont2 == 0 || cont2 == horizontal - 1)
                map[cont][cont2] = 124; // Vertical Line
            else
                map[cont][cont2] = 32; // Space
        }
    }
}

void PrintInterface(int map[vertical][horizontal], int *life)
{

    printf("Life: %d\n\n", *life);
    for (int cont = 0; cont < vertical; cont++)
    {
        for (int cont2 = 0; cont2 < horizontal; cont2++)
        {
            printf("%c", map[cont][cont2]);
        }
        printf("\n");
    }
}

void Movement(int map[vertical][horizontal], int left, int right, int up, int down, int *life)
{

    for (int cont = 0; cont < vertical; cont++)
    {
        for (int cont2 = 0; cont2 < horizontal; cont2++)
        {
            if (left == 1 && map[cont][cont2] == '@')
            {
                left = CollisionLeft(map, left, cont, cont2, life);
                break;
            }
            else if (right == 1 && map[cont][cont2] == '@')
            {
                right = CollisionRight(map, right, cont, cont2, life);
                break;
            }
            else if (up == 1 && map[cont][cont2] == '@')
            {
                up = CollisionUp(map, up, cont, cont2, life);
                break;
            }
            else if (down == 1 && map[cont][cont2] == '@')
            {
                down = CollisionDown(map, down, cont, cont2, life);
                break;
            }
            if (left == 0 && right == 0 && up == 0 && down == 0)
                break;
        }
    }
    //Food(map);
    PrintInterface(map, life);
}

void Game()
{
    int map[vertical][horizontal];
    int cont, cont2;
    int life = 3;
    ResetMatrix(map);
    map[vertical / 2][horizontal / 2] = '@';

    for (int left = 0, right = 0, up = 0, down = 0, input = 0;;)
    {
        system("clear");
        Movement(map, left, right, up, down, &life);
        if (life == 0)
            break;
        left = 0, right = 0, up = 0, down = 0, input = 0;
        input = tolower(getch());
        if (input == 119)
            up++;
        else if (input == 115)
            down++;
        else if (input == 97)
            left++;
        else if (input == 100)
            right++;
    }
    system("clear");
    printf("Game Over.\n\n");
}

int main()
{

    char op;
    printf("Snake Game\n\n2. Start the Game\n1. Credits\n0. Exit\n\n");

    op = getchar();
    if (op == '0')
        return 0;
    else if (op == '1')
    {
        system("clear");
        printf("Gustavo Silva.\nStack Overflow Geniuses.\n\n");
    }
    else if (op == '2')
    {
        system("clear");
        Game();
    }
    return 0;
}