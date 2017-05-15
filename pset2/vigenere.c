/**
 * vigenere.c
 *
 * Fred Campos
 * fcf.camposx@gmail.com
 *
 * Uses the Vigenere cipher to encrypt a message
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key, code;
    int mod;
    
    // error checking
    if (argc != 2) // makes sure the key is only one word
    {
        printf("Please enter a valid key!\n");
        return 1;
    } 
    for (int i = 0, n = strlen(argv[1]); i < n; i++) // makes sure non-alphabetic characters were entered
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Please enter a valid key!\n");
            return 1;  
        }
    }
    
    key = argv[1];
    mod = strlen(key);
    code = GetString();
    
    // iterate through the key, making it all upper case and setting A to 0
    for (int i = 0; i < mod; i++)
        {
            key[i] = toupper(key[i]) - 'A';
        }
    
    
    // iterates through the message and applies the key to each letter
    // loops through the letters of the key on a seperate counter
    // math sets the current letter to 0 index to do modular math
    for (int i = 0, j = strlen(code), k = 0; i < j; i++)
        {
            if (code[i] >='a' && code[i] <= 'z')
            {
                printf("%c", ((((code[i] - 'a') + key[k % mod]) % 26) + 'a'));
                k ++;
            }
            else if (code[i] >='A' && code[i] <= 'Z')
            {
                printf("%c", ((((code[i] - 'A') + key[k % mod]) % 26) + 'A'));
                k++;
            }
            else
            {
                printf("%c", code[i]);
            }
        }
    printf("\n");    
    return 0;
    
}