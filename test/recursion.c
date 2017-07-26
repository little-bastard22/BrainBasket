#include <stdio.h>
#include <cs50.h>
#include <crypt.h>
#include <string.h>



//declarations
bool key_found = false; //control var for loop break
char check[14]; //for input hash string
char key[14]; // key to test against check
char alphabet[54]; //lower+uppercase + extra /0
int key_ctr; //control for populating alphabet
int n = 0; //for printing the total number of tested strings

int combinations (char *str, int idx, int max_len)
{
    unsigned char c;
    int len = 1;
    while (len < max_len)
    {
        if (idx < (len - 1)) {
            for (int i = 0; i <= 51; ++i) {
                c = alphabet[i];
                str[idx] = c;
                combinations(str, idx + 1, max_len);
            }
            
        } 
        else 
        {
            for (int i = 0; i <= 51; ++i) 
            {
                c = alphabet[i];
                str[idx] = c;
                if (strcmp(str, "rofl") == 0)
                {
                    printf("%s\n", str);
                    n++;
                    return 0;
                }
                n++;
            }
        }
        len++;
    }
    return 1;
}

int main(void)

#define LEN 4

{
    
    
    //populates alphabet array with uppercase chars
    for (char c = 'A'; c <= 'Z'; c++)
    {
        key_ctr = c-65;
        alphabet[key_ctr] = c;
    }
    
    //populates alphabet array with lowercase chars
    for (char c = 'a'; c <= 'z'; c++)
    {
        key_ctr++;
        alphabet[key_ctr] = c;
        
    }
    
    //adds extra /0 char to the end of the array
    //alphabet[52] = '\0';
    
    char str[LEN + 2];

    memset(str, 0, LEN + 1);

    printf("%d", combinations(str, 0, LEN));
    
    //prints number of tested strings
    printf("%d words tested\n",n);
}