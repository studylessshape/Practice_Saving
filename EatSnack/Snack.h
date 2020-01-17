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
}Snack;

typedef struct
{
    char paper[MAX_WIDTH][MAX_LENGTH];
}Paper;
void CreateFood(int *x, int *y, Snack snack, Paper *paper)
{
    int i;
    while(!isCreateFood)
    {
        srand((unsigned int)time(NULL));
        *x = 1 + rand()%(MAX_WIDTH - 2);
        srand((unsigned int)time(NULL));
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
    for(i = 0;i < MAX_WIDTH;i ++)
    {
        for(j = 0;j < MAX_LENGTH;j ++)
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
    for(i = 0; i < snack->length;i ++)
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
    for(i = 0;i < MAX_WIDTH;i ++)
    {
        for(j = 0;j <MAX_LENGTH;j ++)
        {
            printf("%c", paper.paper[i][j]);
        }
        printf("\n");
    }
}
