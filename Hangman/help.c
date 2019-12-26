#include"gameDefine.h"
void help()
{
    FILE *fhelp;
    if(!(fhelp = fopen("help.hangman", "r")))
    {
        MessageBox(NULL, TEXT("Open help failed!\n"), TEXT("Error"), MB_OK);
        exit(0);
    }
    while(!feof(fhelp))
    {
        printf("%c", fgetc(fhelp));
    }
    fclose(fhelp);
    printf("Press any key return...\n");
    getchar();
}
