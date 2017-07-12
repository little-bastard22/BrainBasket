#include "stdio.h"
#include "cs50.h"
#include "math.h"

int main(void)
{
    printf("O hai! How much change is owed?\n");
    int i_change = round(get_float() * 100);
    while (i_change < 0)
    {
        printf("How much change is owed?\n");
        i_change = round(get_float() * 100);
    }
    int quarters = i_change / 25;
    i_change %= 25;
    int dimes = i_change / 10;
    i_change %= 10;
    int nickels = i_change / 5;
    i_change %= 5;
    int pennies = i_change;
    printf("%d\n", quarters + dimes + nickels + pennies);
}