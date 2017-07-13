#include <stdio.h>
#include <cs50.h>
#include <string.h>

//capitalizes character
char capital_c(char c)
{
    c -= 32;
    return c;
}

int main(void)
{
    //init and input
    char prev_c = ' '; //inits with space to catch first letter
    char cur_c = 'a';
    string s = get_string();
   
    //searches for spaces in string
    for (int i=0; i < strlen(s); i++)
    {
        cur_c = s[i];
        
        // takes first letter after space, if not another space
        if (prev_c == ' ' && cur_c != ' ')
        {
        
            // capitalizes letter if needed 
            if (cur_c >= 97 && cur_c <= 122) 
            {
                cur_c = capital_c(cur_c);
            } 
                
            //prints correct letter    
            printf("%c", cur_c);
        }
        
        //changes previous letter
        prev_c = cur_c;
    }
   printf("\n");
}