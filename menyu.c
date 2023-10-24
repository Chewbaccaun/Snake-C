#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <stdbool.h>
#define horizontal 100
#define vertical 30

int ResetLife(int map[vertical][horizontal], int *life)
{
    map[vertical / 2][horizontal / 2] = '@';
    return *life - 1;
}

void Food(int map[vertical][horizontal])
{
    int rand1, rand2;
    bool check = false;
    do
    {
        rand1 = rand() % (vertical - 1);
        rand2 = rand() % (horizontal - 1);
        if (map[rand1][rand2] != '@' && rand1 != 0 && rand2 != 0)
            map[rand1][rand2] = '*';

        for(rand1 = 1; rand1 < vertical; rand1++)
        {
            for(rand2 = 1; rand2 < horizontal; rand2++)
            {
                if(map[rand1][rand2] == '*') check = true;
            }
        }
    } while (check == false);
}

int CollisionLeft(int map[vertical][horizontal], int left, int cont, int cont2, int *Life, int *score)
{
    if (map[cont][cont2 - 1] == '*')
    {
        map[cont][cont2 - 1] = '@';
        Food(map);
        ++*score;
    }
    else
        map[cont][cont2 - 1] = '@';
    if (map[cont][0] == '@')
    {
        *Life = ResetLife(map, Life);
        map[cont][0] = '|'; 
    }
    map[cont][cont2] = ' ';
    return left = 0;
}

int CollisionRight(int map[vertical][horizontal], int right, int cont, int cont2, int *Life, int *score)
{
    if (map[cont][cont2 + 1] == '*')
    {
        map[cont][cont2 + 1] = '@';
        Food(map);
        ++*score;
    }
    else
        map[cont][cont2 + 1] = '@';
    if (map[cont][horizontal - 1] == '@')
    {
        *Life = ResetLife(map, Life);
        map[cont][horizontal - 1] = '|';
    }
    map[cont][cont2] = ' ';
    return right = 0;
}

int CollisionUp(int map[vertical][horizontal], int up, int cont, int cont2, int *Life, int *score)
{
    if (map[cont - 1][cont2] == '*')
    {
        map[cont - 1][cont2] = '@';
        Food(map);
        ++*score;
    }
    map[cont - 1][cont2] = '@';
    if (map[0][cont2] == '@')
    {
        *Life = ResetLife(map, Life);
        map[0][cont2] = '=';
    }
    map[cont][cont2] = ' ';
    return up = 0;
}

int CollisionDown(int map[vertical][horizontal], int down, int cont, int cont2, int *Life, int *score)
{
    if (map[cont + 1][cont2] == '*')
    {
        map[cont + 1][cont2] = '@';
        Food(map);
        ++*score;
    }
    map[cont + 1][cont2] = '@';
    if (map[vertical - 1][cont2] == '@')
    {
        *Life = ResetLife(map, Life);
        map[vertical - 1][cont2] = '=';
    }
    map[cont][cont2] = ' ';
    return down = 0;
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
                map[cont][cont2] = '=';
            else if (cont2 == 0 || cont2 == horizontal - 1)
                map[cont][cont2] = '|';
            else
                map[cont][cont2] = ' ';
        }
    }
}

void PrintInterface(int map[vertical][horizontal], int life, int score)
{

    printf("Life: %d\t\tScore: %d\n\n", life, score);
    for (int cont = 0; cont < vertical; cont++)
    {
        for (int cont2 = 0; cont2 < horizontal; cont2++)
        {
            printf("%c", map[cont][cont2]);
        }
        printf("\n");
    }
}

void Movement(int map[vertical][horizontal], int left, int right, int up, int down, int *life, int *score, int *MovCheck)
{
    for (int cont = 0; cont < vertical; cont++)
    {
        for (int cont2 = 0; cont2 < horizontal; cont2++)
        {
            if (left == 1 && map[cont][cont2] == '@')
            {
                left = CollisionLeft(map, left, cont, cont2, life, score);
                break;
            }
            else if (right == 1 && map[cont][cont2] == '@')
            {
                right = CollisionRight(map, right, cont, cont2, life, score);
                break;
            }
            else if (up == 1 && map[cont][cont2] == '@')
            {
                up = CollisionUp(map, up, cont, cont2, life, score);
                break;
            }
            else if (down == 1 && map[cont][cont2] == '@')
            {
                down = CollisionDown(map, down, cont, cont2, life, score);
                break;
            }
            if (left == 0 && right == 0 && up == 0 && down == 0)
            {
                *MovCheck = 0;
                break;
            }
        }
    }
}

void Game()
{
    int map[vertical][horizontal];
    int cont, cont2;
    int life = 3, score = 0, MovCheck = 0;
    ResetMatrix(map);
    map[vertical / 2][horizontal / 2] = '@';
    Food(map);

    for (int left = 0, right = 0, up = 0, down = 0, input = 0;;)
    {
        system("clear");
        Movement(map, left, right, up, down, &life, &score, &MovCheck);
        PrintInterface(map, life, score);
        if (life == 0)
            break;
        left = 0, right = 0, up = 0, down = 0, input = 0;
        input = tolower(getch());
        if (input == 119)
        {
            up++;
            MovCheck = 1;
        }
        else if (input == 115)
        {
            down++;
            MovCheck = 2;
        }
        else if (input == 97)
        {
            left++;
            MovCheck = 3;
        }
        else if (input == 100)
        {
            right++;
            MovCheck = 4;
        }
    }
    system("clear");
    printf("Game Over.\n\n");
}

int main()
{
    srand(time(NULL));
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