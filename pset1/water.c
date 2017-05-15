/**
 * water.c
 *
 * Fred Campos
 * fcf.camposx@gmail.com
 *
 * Display how many bottles of water an 'X'-minute shower would result in
 */
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int minutes;
    int bottles;
    
    printf("minutes: ");
    minutes = GetInt();
    
    bottles = minutes * (192 / 16);
    printf("bottles: %i\n", bottles);
}