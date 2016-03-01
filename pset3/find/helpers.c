/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
    // TODO: implement a searching algorithm
    int beginning = 0;
    int ending = n - 1;
    int middle;

    while (ending >= beginning) 
    {    
        middle = (beginning + ending) / 2; 
        
            //look at middle of list if (binary_search(n, numbers, SIZE))
            if(array[middle] == value)
                //if number found, return true 
                return true;

            //else if middle higher, search left 
            else if(array[middle] > value)
                ending = middle - 1;

            //else if middle lower, search right 
            else if(array[middle] < value)
                beginning = middle + 1;
        
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[],int first, int last)
{
    // TODO: implement an O(n) sorting algorithm
    int pivot,j,temp,i;

     if(first<last)
        {
         pivot=first;
         i=first;
         j=last;

         while(i<j)
            {
             while(values[i]<=values[pivot]&&i<last)
                 i++;
             while(values[j]>values[pivot])
                 j--;
             if(i<j)
                {
                 temp=values[i];
                 values[i]=values[j];
                 values[j]=temp;
                }
            }

         temp=values[pivot];
         values[pivot]=values[j];
         values[j]=temp;
         sort(values,first,j-1);
         sort(values,j+1,last);

        }
    return;
}
