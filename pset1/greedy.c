/**
 * greedy.c
 *
 * Fred Campos
 * fcf.camposx@gmail.com
 *
 * Count how much change, in coins, to return to the user.
 */
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // get float from user to convert to int and use for the rest of program
    float changeowed;

    do
    {
        printf("How much change will you be needing today, good sir?\n");
        printf("Amount: ");
        changeowed = GetFloat();
    }
    while (changeowed <= 0);

    // initialize variables for math to see how many coins will be needed
    int ichangeowed = round(changeowed * 100);
    int coincount, remainder;
    int quarter = 25, dime = 10, nickel = 5, penny = 1;

    // doing the math by division and the modulo remainders
    coincount = ichangeowed / quarter;
    remainder = ichangeowed % quarter;

    coincount = coincount + (remainder / dime);
    remainder = remainder % dime;

    coincount = coincount + (remainder / nickel);
    remainder = remainder % nickel;

    coincount = coincount + (remainder / penny);
    remainder = remainder % penny;

    printf("%i\n", coincount);
}
