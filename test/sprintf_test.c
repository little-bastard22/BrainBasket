#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char filename[8];
    
    for (int i = 0; i<100; i++)
    {
        sprintf(filename, "%03d.jpg\n", i);
        printf("%s", filename);
    }
}