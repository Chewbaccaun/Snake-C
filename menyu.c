#include "lib.h"
#define horizontal 100
#define vertical 30

void ResetLife(int map[vertical][horizontal], int *life)
{
    map[vertical / 2][horizontal / 2] = '@';
    --*life;
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

        for (rand1 = 1; rand1 < vertical; rand1++)
        {
            for (rand2 = 1; rand2 < horizontal; rand2++)
            {
                if (map[rand1][rand2] == '*')
                    check = true;
            }
        }
    } while (check == false);
}

void CollisionUp(int map[vertical][horizontal], int *x, int *y, int *Life, int *score)
{
    if (map[*y - 1][*x] == ' ')
    {
        map[*y - 1][*x] = '@';
        map[*y][*x] = ' ';
        --*y;
    }
    else if (map[*y - 1][*x] == '*')
    {
        map[*y - 1][*x] = '@';
        Food(map);
        ++*score;
        map[*y][*x] = ' ';
        --*y;
    }
    else if (map[*y - 1][*x] == '=')
    {
        ResetLife(map, Life);
        map[*y][*x] = ' ';
        map[vertical / 2][horizontal / 2] = '@';
        *x = horizontal / 2;
        *y = vertical / 2;
    }
}

void CollisionDown(int map[vertical][horizontal], int *x, int *y, int *Life, int *score)
{
    if (map[*y + 1][*x] == ' ')
    {
        map[*y + 1][*x] = '@';
        map[*y][*x] = ' ';
        ++*y;
    }
    else if (map[*y + 1][*x] == '*')
    {
        map[*y + 1][*x] = '@';
        Food(map);
        ++*score;
        map[*y][*x] = ' ';
        ++*y;
    }
    else if (map[*y + 1][*x] == '=')
    {
        ResetLife(map, Life);
        map[*y][*x] = ' ';
        map[vertical / 2][horizontal / 2] = '@';
        *x = horizontal / 2;
        *y = vertical / 2;
    }
}

void CollisionLeft(int map[vertical][horizontal], int *x, int *y, int *Life, int *score)
{
    if (map[*y][*x - 1] == ' ')
    {
        map[*y][*x - 1] = '@';
        map[*y][*x] = ' ';
        --*x;
    }
    else if (map[*y][*x - 1] == '*')
    {
        map[*y][*x - 1] = '@';
        Food(map);
        ++*score;
        map[*y][*x] = ' ';
        --*x;
    }
    else if (map[*y][*x - 1] == '|')
    {
        ResetLife(map, Life);
        map[*y][*x - 1] = '|';
        map[*y][*x] = ' ';
        map[vertical / 2][horizontal / 2] = '@';
        *x = horizontal / 2;
        *y = vertical / 2;
    }
}

void CollisionRight(int map[vertical][horizontal], int *x, int *y, int *Life, int *score)
{
    if (map[*y][*x + 1] == ' ')
    {
        map[*y][*x + 1] = '@';
        map[*y][*x] = ' ';
        ++*x;
    }
    else if (map[*y][*x + 1] == '*')
    {
        map[*y][*x + 1] = '@';
        Food(map);
        ++*score;
        map[*y][*x] = ' ';
        ++*x;
    }
    else if (map[*y][*x + 1] == '|')
    {
        ResetLife(map, Life);
        map[*y][*x] = ' ';
        map[vertical / 2][horizontal / 2] = '@';
        *x = horizontal / 2;
        *y = vertical / 2;
    }
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
    fflush(stdout);
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

void Game()
{
    int map[vertical][horizontal];
    ResetMatrix(map);
    Food(map);
    map[vertical / 2][horizontal / 2] = '@';
    int x = horizontal / 2;
    int y = vertical / 2;
    int life = 3, score = 0, input, lim = 4;
    for (;;)
    {
        system("clear");
        PrintInterface(map, life, score);

        // if (life == 0)
        // break;
        input = tolower(getch());
        if (input == 'w')
            lim = 1;
        else if (input == 'a')
            lim = 2;
        if (input == 's')
            lim = 3;
        else if (input == 'd')
            lim = 4;
        if (input == 'w' || lim == 1)
        {
            CollisionUp(map, &x, &y, &life, &score);
        }
        else if (input == 'a' || lim == 2)
        {
            CollisionLeft(map, &x, &y, &life, &score);
        }
        else if (input == 's' || lim == 3)
        {
            CollisionDown(map, &x, &y, &life, &score);
        }
        else if (input == 'd' || lim == 4)
        {
            CollisionRight(map, &x, &y, &life, &score);
        }
        usleep(50000);
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