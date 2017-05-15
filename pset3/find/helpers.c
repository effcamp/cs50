/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 * 
 */

bool binarysearch(int key, int array[], int low, int high);

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    return binarysearch(value, values, 0, n);
}

bool binarysearch(int key, int array[], int low, int high)
{
    if (high >= low)
    {
        int mid = (low + high) / 2;
        
        if (key == array[mid])
            return true;
        else if (key > array[mid])
            return binarysearch(key, array, mid + 1, high);
        else
            return binarysearch(key, array, low, mid - 1);
    }
    else 
    {
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int i, j, min, tmp;
    
    for (i = 0; i < n-1; i++)
    {
        min = i;
        for (j = i+1; j < n; j++)
        {
            if (values[min] > values[j])
                min = j;
        }
        if (min != i)
        {
            tmp = values[i];
            values[i] = values[min];
            values[min] = tmp;
        }
    }
}
//insertion sort (works)
//    int j, tmp;
//    for(int i = 0; i < n-1; i++)
//    {
//        tmp = values[i];
//        j = i;
//        while(tmp < values[j-1] && j > 0)
//        {
//            values[j] = values[j-1];
//            j--;
//        }
//        values[j] = tmp;
//    }