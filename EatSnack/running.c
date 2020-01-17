#include<stdio.h>
#include"GameManager.h"
void PlayGame()
{
    int isPlayGame = TRUE, frame = 0, status = NOTHING, score = 0, userInput = NODIRECTION,FRAME=5000;
    int food[2];
    Snack snack;
    Paper paper;
    InitializationGame(&paper, &snack);
    CreateFood(&food[0], &food[1], snack, &paper);
    PrintPaper(paper,score);
    while(isPlayGame)
    {
        frame++;
        if(kbhit())
        {
            userInput = GetUserInput(snack);
            if((userInput == UP && snack.direct == DOWN)||(userInput == DOWN && snack.direct == UP)||(userInput == LEFT && snack.direct == RIGHT)||(userInput == RIGHT && snack.direct == LEFT))
            {
                status = DEAD;
                OnDead();
            }
            snack.direct = userInput;
        }
        if(frame == FRAME)
        {
            MoveSnack(&paper, &snack, UNADDLENGTH);
            status = CheckTrigger(snack, food);
            PrintPaper(paper, score);
            frame = 0;
            if(status == EATFOOD)
            {
                MoveSnack(&paper, &snack, ADDLENGTH);
                isCreateFood = FALSE;
                score++;
                CreateFood(&food[0], &food[1], snack, &paper);
                if(score == 10)
                    FRAME /= 2;
                else if(score == 20)
                    FRAME /= 2;
            }
            else if(status == DEAD)
            {
                OnDead();
            }
        }
    }
}
void running()
{
    PlayGame();
}
