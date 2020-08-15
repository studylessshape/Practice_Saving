#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"Direction.h"
#define MAX_WIDTH 28
#define MAX_LENGTH 52
#define TRUE  1
#define FALSE 0
int isCreateFood = FALSE;
typedef struct
{
    int x[MAX_LENGTH * MAX_WIDTH];
    int y[MAX_LENGTH * MAX_WIDTH];
    int direct;
    int length;
} Snack;

typedef struct
{
    char paper[MAX_WIDTH][MAX_LENGTH];
} Paper;
/*
void CreateFood(int *x, int *y, Snack snack, Paper *paper)
{
    int i;
    srand((unsigned int)time(NULL));
    while(!isCreateFood)
    {

        *x = 1 + rand()%(MAX_WIDTH - 2);
        //srand((unsigned int)time(NULL));
        *y = 1 + rand()%(MAX_LENGTH - 2);
        for(i = 0; i < snack.length;i ++)
        {
            if(snack.x[i]==*x || snack.y[i]==*y)
            {
                isCreateFood = FALSE;
                break;
            }
            else
                isCreateFood = TRUE;
        }
    }
    paper->paper[*x][*y] = '$';
}
*/

void CreateFood(int *x, int *y, Snack snack, Paper *paper)
{
    srand((unsigned int)time(NULL));
    int snakeField_max_x = 1;
    int snakeField_max_y = 1;
    int snakeField_min_x = MAX_WIDTH - 2;
    int snakeField_min_y = MAX_LENGTH - 2;

    for(int i = 0; i < snack.length; i ++)
    {
        if(snack.x[i] > snakeField_max_x)
            snakeField_max_x = snack.x[i];
        if(snack.x[i] < snakeField_min_x)
            snakeField_min_x = snack.x[i];
        if(snack.y[i] > snakeField_max_y)
            snakeField_max_y = snack.y[i];
        if(snack.y[i] < snakeField_min_y)
            snakeField_min_y = snack.y[i];
    }

    int chunk = 1 + rand()%8;
    int iter_max_x;
    int iter_min_x;
    int iter_max_y;
    int iter_min_y;

    while(1)
    {
        if(chunk == 1 || chunk == 4 ||chunk == 6)
        {
            iter_max_x = snakeField_min_x - 1;
            iter_min_x = 1;
        }
        else if(chunk == 2 || chunk == 7)
        {
            iter_max_x = snakeField_max_x + 1;
            iter_min_x = snakeField_min_x;
        }
        else if(chunk == 3 || chunk == 5 || chunk == 8)
        {
            iter_max_x = MAX_WIDTH - 2;
            iter_min_x = snakeField_max_x + 1;
        }

        if(chunk >= 1 && chunk <= 3)
        {
            iter_max_y = snakeField_min_y - 1;
            iter_min_y = 1;
        }
        else if(chunk == 4 || chunk == 5)
        {
            iter_max_y = snakeField_max_y + 1;
            iter_min_y = snakeField_min_y - 1;
        }
        else if(chunk >= 6 && chunk <= 8)
        {
            iter_max_y = MAX_LENGTH - 2;
            iter_min_y = snakeField_max_y + 1;
        }
        int count_block = 0;
        for(int i = iter_min_x; i <= iter_max_x && i < MAX_WIDTH - 1 && i >= 1; i ++)
        {
            for(int j = iter_min_y; j <= iter_max_y && j < MAX_LENGTH - 1 && j >= 1; j ++)
            {
                if((i <= iter_max_x && i < MAX_WIDTH - 1 && i >= 1) && (j <= iter_max_y && j < MAX_LENGTH - 1 && j >= 1))
                {
                    if(paper->paper[i][j] == ' ')
                    {
                        count_block ++;
                    }
                    if(paper->paper[i][j] == '*')
                    {
                        count_block = 0;
                        break;
                    }
                }
            }
        }

        if(count_block != 0)
        {
            break;
        }
        else
        {
            chunk++;
            if(chunk > 8)
                chunk = 1;
        }
    }
    if(x != NULL && y != NULL)
    {
        int x_off = iter_max_x - iter_min_x;
        if(x_off<=0)
            x_off = 1;
        int y_off = iter_max_y - iter_min_y;
        if(y_off <=0)
            y_off = 1;
        *x = iter_min_x + rand()%x_off;
        *y = iter_min_y + rand()%y_off;
    }
    paper->paper[*x][*y] = '$';
    return;
}

//Invoke SnackInit when game start
void SnackInit(Snack *snack)
{
    snack->direct = RIGHT;
    snack->x[0] = 14;
    snack->y[0] = 2;
    snack->x[1] = 14;
    snack->y[1] = 1;
    snack->length = 2;
}
//Invoke PaperInit when game start
void PaperInit(Paper *paper)
{
    int i, j;
    for(i = 0; i < MAX_WIDTH; i ++)
    {
        for(j = 0; j < MAX_LENGTH; j ++)
        {
            if(i==0 || i==MAX_WIDTH-1 || j==0 || j == MAX_LENGTH - 1)
                paper->paper[i][j] = '#';
            else
                paper->paper[i][j] = ' ';
        }
    }
}
//Invoke InitializationGame when game start
void InitializationGame(Paper *paper, Snack *snack)
{
    int i;
    SnackInit(snack);
    PaperInit(paper);
    for(i = 0; i < snack->length; i ++)
    {
        if(i == 0)
            paper->paper[snack->x[i]][snack->y[i]] = '@';
        else
            paper->paper[snack->x[i]][snack->y[i]] = '*';
    }
}

void PrintPaper(Paper paper, int score)
{
    int i, j;
    system("cls");
    printf("score:%d\n", score);
    for(i = 0; i < MAX_WIDTH; i ++)
    {
        for(j = 0; j <MAX_LENGTH; j ++)
        {
            printf("%c", paper.paper[i][j]);
        }
        printf("\n");
    }
}
