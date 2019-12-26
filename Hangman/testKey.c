#include<stdio.h>
#include<conio.h>
/**< Test keyboard's number */
void testKey()
{
    char move;
    while(1)
    {
        move = getch();
        printf("%c = %d %0X\n", move, move, move);
    }
}
