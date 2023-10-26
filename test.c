#include "lib.h"
#define horizontal 100
#define vertical 30

int ResetLife(int map[vertical][horizontal], int *life)
{
    map[vertical / 2][horizontal / 2] = '@';
    return *life - 1;
}

void Food(int map[vertical][horizontal])
{
    short int rand1, rand2;
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

void CollisionUp(int map[vertical][horizontal], int up, int *Life, int *score)
{
    short int cont, cont2;
    for (cont = 0; cont < vertical; cont++)
    {
        for (cont2 = 0; cont2 < horizontal; cont2++)
        {
            if (map[cont][cont2] == '@')
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
                break;
            }
        }
    }
}

void CollisionDown(int map[vertical][horizontal], int down, int *Life, int *score)
{
    short int cont, cont2;
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
}

void CollisionLeft(int map[vertical][horizontal], int left, int *Life, int *score)
{
    short int cont, cont2;
    for (cont = 0; cont < vertical; cont++)
    {
        for (cont2 = 0; cont2 < horizontal; cont2++)
        {
            if (map[cont][cont2] == '@')
            {
                break;
            }
        }
    }
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
}

void CollisionRight(int map[vertical][horizontal], int right, int *Life, int *score)
{
    short int cont, cont2;
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
}

void ResetMatrix(int map[vertical][horizontal])
{
    for (short int cont = 0; cont < vertical; cont++)
    {
        for (short int cont2 = 0; cont2 < horizontal; cont2++)
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
    for (short int cont = 0; cont < vertical; cont++)
    {
        for (short int cont2 = 0; cont2 < horizontal; cont2++)
        {
            printf("%c", map[cont][cont2]);
        }
        printf("\n");
    }
}

void Game()
{
    int map[vertical][horizontal], life = 3, score = 0; // Pointer and Matrix
    short int cont, cont2, left = 0, right = 1, up = 0, down = 0, input = 'w';
    ResetMatrix(map);
    map[vertical / 2][horizontal / 2] = '@';
    Food(map);

    for (;;)
    {
        system("clear");
        PrintInterface(map, life, score);
        // if (life == 0)
        // break;
        input = getch();
        if (input == 'w' || input == 'W')
        {
            up++;
            CollisionUp(map, up, &life, &score);
            left = 0, right = 0, down = 0;
        }
        else if (input == 's' || input == 'S')
        {
            CollisionDown(map, down, &life, &score);
            down++;
            left = 0, right = 0, up = 0;
        }
        else if (input == 'a' || input == 'A')
        {
            CollisionLeft(map, left, &life, &score);
            left++;
            right = 0, up = 0, down = 0;
        }
        else if (input == 'd' || input == 'D')
        {
            CollisionRight(map, right, &life, &score);
            right++;
            left = 0, up = 0, down = 0;
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