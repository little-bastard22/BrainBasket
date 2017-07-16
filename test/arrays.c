#include "stdio.h"
#include "cs50.h"

int main (void) {
    int counter = 0;
    int arr [10] = {5,1,1,3,3,3,2,2,2,1};
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 3; j++) 
        {
            if (arr[i] == arr [j])
            {
                counter++;
                break;
            }
        }
        
    }
    printf("%i\n", counter);
}