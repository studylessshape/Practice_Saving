#include "gameDefine.h"
int Menu();
void game();
void help();
void running()
{
    int menu = UNCHOOSE;
    while(1)
    {
        menu = Menu();
        if(menu == GAMESTART)
        {
            game();
        }
        else if(menu == GAMEEXIT)
        {
            printf("Press any key to exit...\n");
            getchar();
            return;
        }
    }
}
int Menu()
{
    char start[12] =">Start", exitGame[12] = " Exit", chelp[12] = " Help";
    int choose = GAMESTART;
    char move;
    bool isChoose = ture;
    while(isChoose)
    {
        system("cls");
        printf("Welcome to Hangman!\n");
        printf("%s\n", start);
        printf("%s\n", exitGame);
        printf("%s\n", chelp);
        move = getch();
        if(move == 72)
        {
            if(choose == GAMESTART)
            {
                ;
            }
            else if(choose == GAMEEXIT)
            {
                choose = GAMESTART;
                start[0] = '>';
                exitGame[0] = ' ';
            }
            else if(choose == GAMEHELP)
            {
                choose = GAMEEXIT;
                exitGame[0] = '>';
                chelp[0] = ' ';
            }
        }
        else if(move == 80)
        {
            if(choose == GAMESTART)
            {
                choose = GAMEEXIT;
                start[0] = ' ';
                exitGame[0] = '>';
            }
            else if(choose == GAMEEXIT)
            {
                choose = GAMEHELP;
                exitGame[0] = ' ';
                chelp[0] = '>';
            }
            else if(choose == GAMEHELP)
            {
                ;
            }
        }
        else if(move == 13)
        {
            if(choose == GAMEHELP)
            {
                printf(":\n");
                help();
            }
            else
                isChoose = false;
        }
    }
    return choose;
}
