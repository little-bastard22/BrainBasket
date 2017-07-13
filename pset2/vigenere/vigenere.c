#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string plaintext;
string keyword;
int k_ctr;

//checks if string contains only alpha chars
bool is_alpha_only(string s)
{
    for (int i=0; i<strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {

            return false;
        }
    }
    return true;
}

//if adjusted char would be out of aplpha range
char resolve_char(char c, int n)
{
    
    //wraps around for capital letters
    if  ((c >= 'A' && c <= 'Z') && c + n > 90)
    {
        return 'A' + n + c - 91;
    }
    
    //wraps around for lowercase
    else if ((c >= 'a' && c <= 'z') && c + n > 122)
    {
        return 'a' + n + c - 123;
    }
    
    //no wrapping around needed
        return c + n;
}

// returns shift for each key
char resolve_k(char c)
{
    
    // for lowercase except 'a'
    if (c > 'A' && c <= 'Z')
    {
        return  c - 'A';
    }
    
    //f or capital except 'A'
    else if (c > 'a' && c <= 'z')
    {
        return c - 'a';
    }
    
    // for 'a', 'A'
    return 0;
}

int main (int argc, string argv[])
{
    
    //checks for number of args and valid CL arg (alpha only)
    if (argc != 2 || !is_alpha_only(argv[1]))
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    
    //inputs
    printf("plaintext: ");
    plaintext = get_string();
    string ciphertext = plaintext; //creates string of correct length
    keyword = argv[1];
    
    k_ctr = 0; //control for wrapping the keyword
    
    
    //iteration over plaintext and ciphering it
    for (int i=0; i < strlen(plaintext); i++)
    {
        
        char cur_c = plaintext[i];
        char cur_k = keyword[k_ctr];
        
        //for non-alpha characters print the same character
        if (!isalpha(cur_c))
        {
            ciphertext[i] = cur_c;
        }
        
        //cipher alpha characters with vigenere
        else
        {
            int n = resolve_k(cur_k);
            ciphertext[i] = resolve_char(cur_c, n);
            
            //wraps around keyword chars
            if (k_ctr == strlen(keyword) - 1 )
                {
                    
                    k_ctr = 0;
                }
            else
                {
                    k_ctr++;
                }

        }
    }
    printf("ciphertext: %s", ciphertext);
    printf("\n");
    return 0;
}