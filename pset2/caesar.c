/**
 * caesar.c
 *
 * Fred Campos
 * fcf.camposx@gmail.com
 *
 *  Uses the Caesar cipher to encrypt a message
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int key;
    string code;
    char crlt, mod;
    
    //error checking
    if (argc != 2 || atoi(argv[1]) == 0) //checks to see if a single, non-zero number was entered
    {
        printf("Please enter a valid key!\n");
        return 1;
    }
    key = atoi(argv[1]);    // converts key to an int
    
    code = GetString();     // gets message from user
    
    
    // iterates through the code applying the key to the letter as necessary 
    // skipping spaces and other non-alphabetic characters and looping back when necessary
    for (int i = 0, n = strlen(code); i < n; i++)
    {
        crlt = code[i];
        if (crlt >= 'a' && crlt <= 'z') // lower case letters
        {
            crlt = crlt - 'a';
            mod = (crlt + key) % 26;
            mod = mod + 'a';
            printf("%c", mod);
        }
        else if (crlt >= 'A' && crlt <= 'Z') // upper case letters
        {
            crlt = crlt - 'A';
            mod = (crlt + key) % 26;
            mod = mod + 'A';
            printf("%c", mod);
        }
        else                                // spaces and other characters
        {
            printf("%c", crlt); 
        }
    }
    
    printf("\n");
    return 0;
}