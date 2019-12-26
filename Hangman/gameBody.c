#include "gameDefine.h"
int getFileLine(FILE *target);
char *getWord(int line, FILE *target);
void startGeuss(char word[], char geuss[], char geuss_in[]);
void game()
{
    srand(time(NULL));
    FILE *dictionary;
    int line, length, i;
    char word[10];
    char geuss[10];
    char geuss_in[7] = {'\0','\0','\0','\0','\0','\0','\0'};
    if(!(dictionary = fopen("dictionary.hangman", "r")))
    {
        MessageBox(NULL, TEXT("Open dictionary failed!\n"), TEXT("Error"), MB_OK);
        exit(0);
    }
    line = getFileLine(dictionary);
    rewind(dictionary);
    line = rand()% line + 1;
    strcpy(word, getWord(line, dictionary));
    length = strlen(word);
    for(i = 0;i < length;i ++)
    {
        geuss[i] = '_';
    }
    geuss[i] = '\0';
    fclose(dictionary);
    startGeuss(word, geuss, geuss_in);
}

int getFileLine(FILE *target)
{
    int count = 0;
    char flag;
    while(!feof(target))
    {
        flag = getc(target);
        if(flag == '\n')
            count++;
    }
    count ++;
    return count;
}

char *getWord(int line, FILE *target)
{
    int count = 0;
    char flag;
    int i = 0;
    static char word[10];
    while(!feof(target))
    {
        if(count == line - 1)
            break;
        flag = getc(target);
        if(flag == '\n')
            count++;
    }
    while((word[i] = fgetc(target)) != '\n' && !feof(target))
    {
        i++;
    }
    word[i] = '\0';
    return word;
}
