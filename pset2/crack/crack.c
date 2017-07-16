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

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    string s_check = argv[1]; //loads argument
    
    //converts string to array of char bcs strings suck
    for (int s = 0; s<13; s++)
    {
         check[s] = s_check[s];
    }
    
    
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
    alphabet[52] = '\0';
    
    
    //iterations for each index - could probably refactor
    
    //first char
    for (int l = 52; l >=0 ; l--)
    {
        key[3] = alphabet[l];
        
        //breaks the loop if found
        if (key_found){break;}
        
        //second char
        for (int k = 52; k >=0 ; k--)
        {
            key[2] = alphabet[k];
            
            //breaks the loop if found
            if (key_found){break;}
            
            //third char
            for (int j = 52; j >=0 ; j--)
            {
                key[1] = alphabet[j];
                
                //breaks the loop if found
                if (key_found){break;}
                
                //fourth char
                for (int i = 52; i >=0; i--)
                {
                    key[0] = alphabet[i];
                    
                    //tests hashed string against input hash
                    if (strcmp(crypt(key, "50"), check) == 0)
                    {
                        printf("%s\n", key); //prints the password
                        key_found = true; //for breaking parent loops
                        break; //breaks the loop
                    }
                    // increment number of tested strings
                    n++;
                }
            }
        }
    }
    
    //prints number of tested strings
    printf("%d words tested\n",n);
}