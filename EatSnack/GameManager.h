#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include"Snack.h"
#ifndef GAMESTATUS
    #define GAMESTATUS
    #define NOTHING 0xa0000
    #define DEAD 0xa0001
    #define EATFOOD 0xa0002
#endif // GAMESTATUS

#ifndef ADDLENGHT
    #define ADLENGTH
    #define UNADDLENGTH 0xb0000
    #define ADDLENGTH 0xb0001
#endif // ADDLENGHT

void Swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void OnDead()
{
    //system("cls");
    printf("Game Over!\nPress any key to exit!\n");
    getchar();
    exit(0);
}
int GetUserInput(Snack snack)
{
    char key = getch();
    switch(key)
    {
        case -32:
            key=getch();
            switch(key)
            {
                case 72 : return UP;
                case 80 : return DOWN;
                case 75 : return LEFT;
                case 77 : return RIGHT;
            }
        default:return snack.direct;
    }
    return NODIRECTION;
}
int CheckTrigger(Snack snack, int food[2])
{
    if(snack.x[0] == MAX_WIDTH - 1 || snack.y[0] == MAX_LENGTH - 1 || snack.x[0] == 0 || snack.y[0] == 0)
    {
        return DEAD;
    }
    else if(snack.x[0] == food[0] && snack.y[0] == food[1])
    {
        return EATFOOD;
    }
    return NOTHING;
}
void MoveSnack(Paper *paper, Snack *snack, int way)
{
    int i;
    if(way==UNADDLENGTH)
        paper->paper[snack->x[snack->length - 1]][snack->y[snack->length - 1]] = ' ';
    else if(way==ADDLENGTH)
        snack->length++;
    for(i = snack->length - 1;i >= 1;i --)
    {
        snack->x[i] = snack->x[i - 1];
        snack->y[i] = snack->y[i - 1];
    }
    paper->paper[snack->x[0]][snack->y[0]] = '*';
    if(snack->direct == UP)
    {
        snack->x[0]--;
    }
    else if(snack->direct == DOWN)
    {
        snack->x[0]++;
    }
    else if(snack->direct == LEFT)
    {
        snack->y[0]--;
    }
    else if(snack->direct == RIGHT)
    {
        snack->y[0]++;
    }
    else if(snack->direct == NODIRECTION)
    {
        MessageBox(NULL, TEXT("蛇没有移动方向！"), TEXT("出错了！"), MB_OK);
        exit(0);
    }
    if(paper->paper[snack->x[0]][snack->y[0]] == '*')
        OnDead();
    paper->paper[snack->x[0]][snack->y[0]] = '@';
}


