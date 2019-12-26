#include "gameDefine.h"
void printUI(int wrong, char geuss_in[], char geuss[]);
int check(char word[], char chGeuss);
void startGeuss(char word[], char geuss[], char geuss_in[])
{
    int count = 0, wrongCount = 0, inCount = 0, length = strlen(word), trueCount = 0;
    char input, *user_input = NULL;
    while(count <= 7)
    {
        printUI(wrongCount, geuss_in, geuss);
        if(trueCount == length)
        {
            printf("YOU WIN!\n");
            getchar();
            break;
        }
        else if(count==7)
        {
            printf("YOU LOSE!\n");
            getchar();
            break;
        }
        while((input = getchar())!='\n')
        {
            inCount++;
            user_input = (char *)realloc(user_input, inCount * sizeof(char));
            *(user_input + inCount - 1) = input;
        }
        *(user_input + inCount) = '\0';
        char *release;
        release = user_input;
        if(inCount > 1|| inCount == 0||(*user_input<'a'&&*user_input>'Z')||(*user_input>'z')||(*user_input<'A'))
        {
            user_input = NULL;
            free(release);
            inCount = 0;
            printf("That is invalid input!\n");
            getchar();
            continue;
        }
        inCount = 0;
        geuss_in[count] = *user_input;
        if(*user_input>='a'&&*user_input<='z')
                *user_input-=32;
        count++;
        if(check(word, *user_input))
        {
            for(int i = 0;i < length;i++)
            {
                if(word[i] == *user_input)
                {
                    geuss[i] = *user_input;
                    trueCount++;
                }
            }
            user_input = NULL;
            free(release);
            printf("That is true!\n");
            getchar();
        }
        else
        {
            user_input = NULL;
            free(release);
            printf("That is wrong!\n");
            getchar();
            wrongCount++;
        }
    }
}

void printUI(int wrong, char geuss_in[], char geuss[])
{
    system("cls");
    int length = strlen(geuss_in);
    printf(" Hangman [");
    for(int i =0;i < length;i++)
    {
        printf("\'%c\'", geuss_in[i]);
        if(i!=length-1)
            printf(",");
    }
    printf("]\n");
    if(!wrong)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    else if(wrong == 1)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "    O   :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    else if(wrong == 2)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "    O   :\n"
               "    :   :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    else if(wrong == 3)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "    O   :\n"
              "   \\:   :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    else if(wrong == 4)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "    O   :\n"
              "   \\:/  :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    else if(wrong == 5)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "    O   :\n"
              "   \\:/  :\n"
               "    :   :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    else if(wrong == 6)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "    O   :\n"
              "   \\:/  :\n"
               "    :   :\n"
               "   /    :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    else if(wrong == 7)
    {
        printf(" _______\n"
               ":   :  \\:\n"
               "    O   :\n"
              "   \\:/  :\n"
               "    :   :\n"
               "   / \\  :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "        :\n"
               "       ---\n");
    }
    printf("%s\n", geuss);
}
//if it is existent,
int check(char word[], char chGeuss)
{
    int length = strlen(word), i;
    for(i = 0;i < length;i++)
    {
        if(word[i] == chGeuss)
            return 1;
    }
    return 0;
}
