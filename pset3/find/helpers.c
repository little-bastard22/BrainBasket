/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int low = 0; //first index to search
    int mid = n/2; //middle index
    int high = n; //last index to search
    // if checked everything (low = high), break loop
    while (low <= high)
    {
        mid = (low + high)/2; //finds middle index
        
        //if found, return true
        if (value == values[mid])
        {
            return true;
        }
        //throw away upper half
        else if (value < values[mid])
        {
            high = mid - 1;
        }
        //throw away lower half
        else
        {
            low = mid + 1;
        }
    }
    
    //if not found, return false
    return false;
}




/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int sort_arr[65536] = {0};
    int value;
    int ctr = 0;
    
    //creates and populates sorting array 
    for (int i = 0; i < n; i++)
    {
        value = values[i];
        sort_arr[value]++;
    }
    
    //adds sorted values to array
    for (int i = 0; i < 65536; i++)
    {
        //only if at least one occurence
        if (sort_arr[i]>0)
        {
            do
            {
                //adds member to the next position in array
                values[ctr] = i;
                ctr++;
                sort_arr[i]--;
            }
            //adds all the members of same value
            while (sort_arr[i] > 0);
        }
    }
    return;
}
