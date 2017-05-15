/**
 * mario.c
 * mofe comfy
 * 
 * Fred Campos
 * fcf.camposx@gmail.com
 *
 * Takes height from user to create a full pyramid similar to Mario games.
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


    // created spaces and # based on how high the pyramid is
    for (int i = 1; i <= height; i++)
    {
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
