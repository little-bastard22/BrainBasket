#include "stdio.h"
#include "cs50.h"
#include <string.h>

char capital_c(char c)
{
    c -= 32;
    return c;
}

int main(void)
{
   char prev_c = ' ';
   char cur_c = 'a';
   string s = get_string();
   for (int i=0; i < strlen(s); i++)
   {
       cur_c = s[i];
       if (prev_c == ' ' && cur_c != ' ')
           {
                if (cur_c >= 97 && cur_c <= 122) 
                {
                    printf("%c", capital_c(cur_c));
                } 
                else
                {
                    printf("%c", cur_c);
                }
            }
    prev_c = cur_c;
   }
   printf("\n");
}