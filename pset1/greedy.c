#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //input + conversion to cents
    printf("O hai! How much change is owed?\n");
    int i_change = round(get_float() * 100);
    
    //repeats for negative input
    while (i_change < 0)
    {
        printf("How much change is owed?\n");
        i_change = round(get_float() * 100);
    }
    
    // get number of coins, remove paid amount and repeat
    int quarters = i_change / 25;
    i_change %= 25; 
    int dimes = i_change / 10;
    i_change %= 10;
    int nickels = i_change / 5;
    i_change %= 5;
    int pennies = i_change;
    
    //print sum of change
    printf("%d\n", quarters + dimes + nickels + pennies);
}