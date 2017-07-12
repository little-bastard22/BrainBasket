#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string plaintext;
string keyword;
int k_ctr;

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

char resolve_char(char c, int n)
{
    char result;
    if  ((c >= 'A' && c <= 'Z') && c + n > 90)
    {
        result = 'A' + n + c - 91;
        return result;
    }
    else if ((c >= 'a' && c <= 'z') && c + n > 122)
    {
        result = 'a' + n + c - 123;
        return result;
    }
    else
    {
        result = c + n;
        return result;
    }
}

char resolve_k(char c)
{
    char result;
    if (c > 'A' && c <= 'Z')
    {
        result = c - 'A';
        return  result;
    }
    else if (c > 'a' && c <= 'z')
    {
        result = c - 'a';
        return result;
    }
    return 0;
}

int main (int argc, string argv[])
{
    if (argc != 2 || !is_alpha_only(argv[1]))
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    
    printf("plaintext: ");
    plaintext = get_string();
    string ciphertext = plaintext;
    keyword = argv[1];
    
    k_ctr = 0;
    
    for (int i=0; i < strlen(plaintext); i++)
    {
        char cur_c = plaintext[i];
        char cur_k = keyword[k_ctr];
        if (!isalpha(cur_c))
        {
            ciphertext[i] = cur_c;
        }
        else
        {
            int n = resolve_k(cur_k);
            ciphertext[i] = resolve_char(cur_c, n);
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