#include<stdio.h>
#include<stdlib.h>
int number;
int count;
int pos[2];
/*
 *  Function declare
*/
char GameStart();
void Option();
void PrintLight(char light[11][11]);
char Initialization(char light[11][11]);
int inputPosition(char light[11][11]);
char ModifyArray(char light[11][11]);
int JudgeSystem(char light[11][11]);
/*
 *  Main
*/
int main()
{
    int judge;
    pos[0]=-1;
    pos[1]=-1;
    char light[11][11];
    while(1)
    {
        if(GameStart() == '-')
        {
            printf("\n");
            system("pause");
            return 0;
        }
        Option();
        getchar();
        Initialization(light);
        while(number != 0)
        {
            PrintLight(light);
            judge = inputPosition(light);
            getchar();
            if(judge == 0)
                break;
            judge = 0;
            ModifyArray(light);
            judge = JudgeSystem(light);
            if(judge == 1)
            {
                PrintLight(light);
                printf("End!You win!\n");
                printf("Your step number is %d\n", count);
                system("pause");
                break;
            }
        }
    }
}
/*
 *  Function define
*/
char GameStart()
{
    char start;
    system("cls");
    printf("\t ###    ###      ##   ####### ##   ## ########\n"
           "\t# $ #   # #          # ###### ##   ## ########\n"
           "\t# $ #   # #      ##  # #      #######    ##\n"
           "\t ###    # #      ##  # # #### #######    ##\n"
           "\t #=#    # #####  ##  # ###### ##   ##    ##\n"
           "\t  #     #######  ##   ######  ##   ##    ##    made by Ñ§ÉÙºÎ\n");
    printf("\t\t  - Enter to Start -\n");
    printf("\t\t    - '-' to Exit -\n");
    printf("\t  In this game,you need to open all light\n");
    printf("\t\t'O' is open and '-' is close\n");
    while(1)
    {
        printf("\t\t\t    ");
        start = getchar();
        getchar();
        if(start == '\n' || start == '-')
        {
            break;
        }
    }
    return start;
}

void Option()
{
    system("cls");
    printf("The lights form a square array!\n");
    printf("You can input 0 to back opening wherever you are!\n");
    printf("Input the array's side length(max:10): ");
    number = 11;
    while(number>10 || (number != 0 &&number < 3))
    {
        scanf("%d", &number);
        if(number > 10)
        {
            printf("Too big,please input again: ");
        }
        else if(number < 3 && number !=0)
        {
            printf("Too small,number is more than 3 at least!\n");
            printf("Try again: ");
        }
    }
}

char Initialization(char light[11][11])
{
    int i, j;
    count = 0;
    for(i = 0;i < number;i ++)
    {
        for(j = 0;j < number;j ++)
        {
            light[i][j] = '-';
        }
    }
    return **light;
}

void PrintLight(char light[11][11])
{
    int i, j;
    system("cls");
    printf("|X/Y|");
    for(j = 0;j < number;j ++)
    {
        printf("%d|", j+1);
    }
    printf("\n");
    for(i = 0;i < number;i ++)
    {
        printf("  |%d|", i + 1);
        for(j = 0;j < number;j ++)
        {
            printf("%c ", light[i][j]);
        }
        printf("\n");
    }
    printf("Step Number: %d\n", count);
}

int inputPosition(char light[11][11])
{
    while(1)
    {
        printf("Input position(e.g. X Y): ");
        scanf("%d %d", &pos[0], &pos[1]);
        if(pos[0] == 0 || pos[1] == 0)
        {
            return 0;
        }
        else if(pos[0] > number || pos[1] > number || (pos[0] !=0 && pos[0] < 1) ||(pos[1] != 0 && pos[1] <1))
        {
            printf("Over edge!");
            printf("Try again!\n");
        }
        else
        {
            return 1;
        }
    }
}

char ModifyArray(char light[11][11])
{
    count++;
    //change position
    if(light[pos[1]-1][pos[0]-1] == '-')
    {
        light[pos[1]-1][pos[0]-1] = 'O';
    }
    else if(light[pos[1]-1][pos[0]-1] == 'O')
    {
        light[pos[1]-1][pos[0]-1] = '-';
    }
    //up and down
    if(pos[1] != 1)
    {
        if(light[pos[1] - 2][pos[0]-1] == '-')
        {
            light[pos[1] - 2][pos[0]-1] = 'O';
        }
        else if(light[pos[1] - 2][pos[0]-1] == 'O')
        {
            light[pos[1] - 2][pos[0]-1] = '-';
        }
    }
    if(pos[1] != number)
    {
        if(light[pos[1]][pos[0]-1] == '-')
        {
            light[pos[1]][pos[0]-1] = 'O';
        }
        else if(light[pos[1]][pos[0]-1] == 'O')
        {
            light[pos[1]][pos[0]-1] = '-';
        }
    }
    //left and right
    if(pos[0] != 1)
    {
        if(light[pos[1]-1][pos[0]-2] == '-')
        {
            light[pos[1]-1][pos[0]-2] = 'O';
        }
        else if(light[pos[1]-1][pos[0]-2] == 'O')
        {
            light[pos[1]-1][pos[0]-2] = '-';
        }
    }
    if(pos[0] != number)
    {
        if(light[pos[1]-1][pos[0]] == '-')
        {
            light[pos[1]-1][pos[0]] = 'O';
        }
        else if(light[pos[1]-1][pos[0]] == 'O')
        {
            light[pos[1]-1][pos[0]] = '-';
        }
    }
    return **light;
}

int JudgeSystem(char light[11][11])
{
    int i, j, number_light = 0;
    for(i = 0;i < number;i ++)
    {
        for(j = 0;j < number;j ++)
        {
            if(light[i][j] == 'O')
            {
                number_light ++;
            }
        }
    }
    if(number_light == (number * number))
        return 1;
    else
        return 0;
}
