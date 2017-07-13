#include <stdio.h>
#include <cs50.h>


// height = height of pyramid = width of half pyramid without middle space
// width = width of half of the pyramid

void print_floor(width,height) 
{
    
    //prints spaces needed to fill first half
    for (int i = 0; i<height-width; i++) 
    {
        printf(" ");
    }
    
    //prints half of pyramid
    for (int i = 0; i<width; i++) 
    {
        printf("#");
    }
    
    //prints space between two halves
    printf("  ");
    
    //prints second half of pyramid
    for (int i = 0; i<width; i++) 
    {
        printf("#");
    }
    printf("\n");
}

void print_pyramid(height) 
{
    int width = 1; //top level width in "#" per half
    
    //print pyramid's floors
    for (int i = 0; i<height; i++)   
    {
        print_floor(width, height);
        width++; //increment for each level  (+ "#" for each half)
    }
}

//asks for height, if not in interval, asks again
int get_height(void) 
{
    int height = 0;
    do
    {
        printf("Height:");
        height = get_int();
    }
    while (height<0 || height>23);
    return height;
}

int main(void) 
{
    int height = get_height(); //get height
    print_pyramid(height); //prints pyramid
}