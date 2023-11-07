#include "lib.h"
#define horizontal 18
#define vertical 18
void DecreaseLife(int map[vertical][horizontal], int *life, int *lim)
{
    map[vertical / 2][horizontal / 2] = 'o';
    --*life;
    *lim = 'd';
}

void CreateFood(int map[vertical][horizontal])
{
    short int rand1, rand2;
    bool check = false;
    do
    {
        rand1 = rand() % (vertical - 1);
        rand2 = rand() % (horizontal - 1);
        if (map[rand1][rand2] == ' ' && rand1 != 0 && rand2 != 0)
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

void FillMatrix(int map[vertical][horizontal], int *score)
{
    *score = 1;
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
    CreateFood(map);
}

void SnakeBody(int map[vertical][horizontal], int xx[], int yy[], int *x, int *y, int *score)
{
    if (*score > 0)
    {
        for (short int cont = *score - 1; cont > 0; cont--)
        {
            xx[cont] = xx[cont - 1];
            yy[cont] = yy[cont - 1];
        }
        xx[0] = *x;
        yy[0] = *y;
        map[*y][*x] = '@';
        map[yy[*score - 1]][xx[*score - 1]] = ' ';
    }
    else
    {
        map[*y][*x] = ' ';
    }
}

void CollisionUp(int map[vertical][horizontal], int xx[], int yy[], int *x, int *y, int *Life, int *score, int *lim, int *highScore)
{
    switch (map[*y - 1][*x])
    {
    case ' ':
        map[*y - 1][*x] = '^';
        SnakeBody(map, xx, yy, x, y, score);
        --*y;
        break;

    case '*':
        map[*y - 1][*x] = '^';
        CreateFood(map);
        xx[*score] = *x;
        yy[*score] = *y;
        ++*score;
        SnakeBody(map, xx, yy, x, y, score);
        --*y;
        break;

    default:
        if (*score > *highScore)
            *highScore = *score;
        DecreaseLife(map, Life, lim);
        map[vertical / 2][horizontal / 2] = '^';
        *x = horizontal / 2;
        *y = vertical / 2;
        FillMatrix(map, score);
        break;
    }
}

void CollisionDown(int map[vertical][horizontal], int xx[], int yy[], int *x, int *y, int *Life, int *score, int *lim, int *highScore)
{
    switch (map[*y + 1][*x])
    {
    case ' ':
        map[*y + 1][*x] = 'v';
        map[*y][*x] = ' ';
        SnakeBody(map, xx, yy, x, y, score);
        ++*y;
        break;

    case '*':
        map[*y + 1][*x] = 'v';
        CreateFood(map);
        xx[*score] = *x;
        yy[*score] = *y;
        ++*score;
        SnakeBody(map, xx, yy, x, y, score);
        ++*y;
        break;

    default:
        if (*score > *highScore)
            *highScore = *score;
        DecreaseLife(map, Life, lim);
        map[vertical / 2][horizontal / 2] = 'v';
        *x = horizontal / 2;
        *y = vertical / 2;
        FillMatrix(map, score);
        break;
    }
}

void CollisionLeft(int map[vertical][horizontal], int xx[], int yy[], int *x, int *y, int *Life, int *score, int *lim, int *highScore)
{
    switch (map[*y][*x - 1])
    {
    case ' ':
        map[*y][*x - 1] = '<';
        map[*y][*x] = ' ';
        SnakeBody(map, xx, yy, x, y, score);
        --*x;
        break;

    case '*':
        map[*y][*x - 1] = '<';
        CreateFood(map);
        xx[*score] = *x;
        yy[*score] = *y;
        ++*score;
        SnakeBody(map, xx, yy, x, y, score);
        --*x;
        break;

    default:
        if (*score > *highScore)
            *highScore = *score;
        DecreaseLife(map, Life, lim);
        map[*y][*x - 1] = '|';
        map[vertical / 2][horizontal / 2] = '<';
        *x = horizontal / 2;
        *y = vertical / 2;
        FillMatrix(map, score);
        break;
    }
}

void CollisionRight(int map[vertical][horizontal], int xx[], int yy[], int *x, int *y, int *Life, int *score, int *lim, int *highScore)
{
    switch (map[*y][*x + 1])
    {
    case ' ':
        map[*y][*x + 1] = '>';
        map[*y][*x] = ' ';
        SnakeBody(map, xx, yy, x, y, score);
        ++*x;
        break;

    case '*':
        map[*y][*x + 1] = '>';
        CreateFood(map);
        xx[*score] = *x;
        yy[*score] = *y;
        ++*score;
        SnakeBody(map, xx, yy, x, y, score);
        ++*x;
        break;

    default:
        if (*score > *highScore)
            *highScore = *score;
        DecreaseLife(map, Life, lim);
        map[*y][*x - 1] = '|';
        map[vertical / 2][horizontal / 2] = '<';
        *x = horizontal / 2;
        *y = vertical / 2;
        FillMatrix(map, score);
        break;
    }
}

void PrintInterface(int map[vertical][horizontal], int *life, int *score, int *highScore)
{
    fflush(stdout);
    printf("Life: %d  Score: %d  Highest Score: %d\n\n", *life, *score, *highScore);
    for (short int cont = 0; cont < vertical; cont++)
    {
        for (short int cont2 = 0; cont2 < horizontal; cont2++)
        {
            printf("%c", map[cont][cont2]);
        }
        printf("\n");
    }
}

void Input(int map[vertical][horizontal], int xx[], int yy[], int *x, int *y, int *life, int *score, int *lim, int *buffer, int *highScore)
{
    short int input;
    int slowdown = 200000 / (vertical * horizontal);
    input = tolower(getch());
    if (input == 'w' || input == 'a' || input == 's' || input == 'd')
    {
        *buffer = *lim;
        *lim = input;
    }
    if (*lim == 'w' && *buffer != 's')
    {
        CollisionUp(map, xx, yy, x, y, life, score, lim, highScore);
        PrintInterface(map, life, score, highScore);
        usleep(200000 - (slowdown * *score));
    }
    else if (*lim == 'a' && *buffer != 'd')
    {
        CollisionLeft(map, xx, yy, x, y, life, score, lim, highScore);
        PrintInterface(map, life, score, highScore);
        usleep(200000 - (slowdown * *score));
    }
    else if (*lim == 's' && *buffer != 'w')
    {
        CollisionDown(map, xx, yy, x, y, life, score, lim, highScore);
        PrintInterface(map, life, score, highScore);
        usleep(200000 - (slowdown * *score));
    }
    else if (*lim == 'd' && *buffer != 'a')
    {
        CollisionRight(map, xx, yy, x, y, life, score, lim, highScore);
        PrintInterface(map, life, score, highScore);
        usleep(200000 - (slowdown * *score));
    }
    else
    {
        *lim = *buffer;
    }
}

void Game()
{
    int map[vertical][horizontal];
    int x = horizontal / 2;
    int y = vertical / 2;
    int life = 3, score, lim = 'd', buffer = 50000, highScore = 1;
    int xx[(horizontal - 1) * (vertical - 1)], yy[(horizontal - 1) * (vertical - 1)];
    FillMatrix(map, &score);
    map[vertical / 2][horizontal / 2] = '>';
    for (;;)
    {
        system("clear");
        Input(map, xx, yy, &x, &y, &life, &score, &lim, &buffer, &highScore);
        if (life == 0)
            break;
    }
    system("clear");
    printf("Game Over.\n\n");
}

int main()
{
    srand(time(NULL));
    char op;
    printf("Snake Game\n\n1. Start the Game\nAny other. Exit\n\n");

    switch (op = getchar())
    {
    case '1':
        system("clear");
        Game();
        break;
    default:
        system("clear");
        printf("Exiting.");
        break;
    }
    return 0;
}