/**
 * mario.c
 *
 * Fred Campos
 * fcf.camposx@gmail.com
 *
 * Takes height from user to create a half pyramid similar to Mario games.
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    // prompt user for number between 1 and 23
    printf("Enter a number between 1 and 23\n");

    do
    {
        printf("Height:");
        height = GetInt();
    }
    while (height < 0 || height > 23);

    int i = 0;

    // created spaces and # based on how high the half-pyramid is
    while (i < height)
    {
        for (int j = height - i; j > 1; j--)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 2; k++)
        {
            printf("#");
        }
        printf("\n");
        i++;
    }
}    
