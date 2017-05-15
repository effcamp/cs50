/**
 * intials.c
 *
 * Fred Campos
 * fcf.camposx@gmail.com
 *
 * Takes names from the user to and gives back the person's initials
 */
 
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string name = GetString();
    
    // prints the first letter in upper case
    printf ("%c", toupper(name[0]));
    // Iterates through the string and looks for a space to print the next letter in upper case
    for (int i = 0, j = strlen(name); i < j; i++)
    {
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i+1]));
        }
    }
    printf("\n");
}