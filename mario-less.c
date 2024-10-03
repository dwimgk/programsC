#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int height = get_int("Pyramid height?\n");


    for (int i = 1; i <= height; i++)
    {
        for(int length = height -i; length > 0; length = length - 1)
        {
            printf(" ");
        }
        for(int j=0; j<i;j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
