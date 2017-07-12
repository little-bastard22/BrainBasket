#include "stdio.h"
#include "cs50.h"

//valid visa number returns true
bool is_visa(long long number) 
{
    if ((number>=4000000000000 && number<5000000000000) || (number>=4000000000000000  && number<5000000000000000))
    {
        return true;
    }
    else 
    {
        return false; 
    }

}

//valid mastercard number returns true
bool is_mastercard(long long number) 
{
    if (number>=5100000000000000 && number<5600000000000000)
    {   
        return true;
    } 
    else 
    {
        return false;
    }
}

//valid amex number returns true
bool is_amex(long long number) 
{
    if ((number>=340000000000000 && number<350000000000000) || (number>=370000000000000  && number<380000000000000))
    {
        return true;
    } 
    else 
    {
        return false;
    }
}


int get_digit_sum(number) 
{
    int digit;
    int result = 0;
    while (number !=0) 
    {
        digit = number % 10;
        number = (number - digit)/10;
        result += digit;
    }
    return result;
}


bool is_valid_number(long long n) 
{
    int control = 1; //ordinality of digit (backwards)
    int sum =0; //total sum
    int product = 0; //intermediate product
    
    //counts numbers, adding them to sum accordingly
    while (n != 0) 
    {
        product = n % 10;
        n = (n - product)/10;  //removes last digit of the number
        
        //checks even/odd numeral ordinality
            //for even numbers
            if (control % 2 == 0) 
            {
                product *= 2;
                sum += get_digit_sum(product);
            }
            //for odd numbers
            else 
            {
                sum += product;
            }   
        control++;
    }
        
    //checks if sum is divisible by 10
    if (sum % 10 == 0) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

int main(void)
{
    printf("Number:");
    long long number = get_long_long();
    
    //only checks the type if the number is valid
    if (is_valid_number(number)) 
    {
        
        //prints type according to bool function
        if (is_visa(number)) 
        {
            printf("VISA\n");
        } 
        else if (is_mastercard(number)) 
        {
            printf("MASTERCARD\n");
        } 
        else if (is_amex(number)) 
        {
            printf("AMEX\n");
        }
        //fallback for valid number, not of any type
        else 
        {
            printf("INVALID\n"); 
        }
    }
    else 
    {
        printf("INVALID\n");
        
    } 
}