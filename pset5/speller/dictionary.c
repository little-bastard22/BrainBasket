/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include <stdlib.h>

#include <stdio.h> //temp

#include <ctype.h>

#include "dictionary.h"

_entry zero_node = {
    .is_word = false,
    .entry_arr = { NULL }
};

int words_in_dict = 0;

char to_lower(char c)
{
    const int diff = 'a' - 'A';
    return c + diff;
}

int get_char_pos(char c)
{
    int char_pos = 0;
    if (c == '\'')
    {
        char_pos = 25;
    }
    else
    {
        // if (isalpha(c))
        {
            if (c >= 65 && c <=90)
            {
                c = to_lower(c);
            }
            char_pos = c-97;
        }
    }
    return char_pos;
}


/*
Creates and initializes new node
*/
_entry * create_node()
{
    // allocates memmory for the node
    _entry * new_node = malloc(sizeof(_entry));

    //initialize all pointers to NULL
    for (int i = 0; i<26; i++)
    {
        new_node->entry_arr[i] = NULL;
    }

    //is not terminal node of a word
    new_node->is_word = false;

    //returns pointer to the new node
    return new_node;
}

/*
    Adds word to a trie.
*/
void add_word(const char *word)
{
    char letter = *word;
    int char_pos;

    //sets pointer to zero node
    _entry * add_ptr = &zero_node;

    //iterates over word until end of word
    while (letter != '\n' && letter != '\0')
    {
        //gets array index for the letter
        char_pos = get_char_pos(letter);

        //if the letter's pointer is NULL, creates new node there
        if (add_ptr->entry_arr[char_pos] == NULL)
        {
            add_ptr->entry_arr[char_pos] = create_node();
            add_ptr = add_ptr->entry_arr[char_pos];
            word++;
            letter = *word;
            continue;
        }

        //if the pointer already exists, it follows it
        word++;
        letter = *word;
        add_ptr = add_ptr->entry_arr[char_pos];
    }

    //sets the node as a terminal node of a word
    add_ptr->is_word = true;
    words_in_dict++; //nothing to see here, definitely not cheating!!!
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    char letter = *word;
    int char_pos;

    //sets pointer to zero node
    _entry * check_ptr = &zero_node;

    //iterates over the word until ended
    while (letter != '\0')
    {
        //gets array index for letter
        char_pos = get_char_pos(letter);

        // if the letter's pointer does not exist, word not valid
        if (check_ptr->entry_arr[char_pos] == NULL)
        {
            return false;
        }

        //if the pointer exists, follow it
        check_ptr = check_ptr->entry_arr[char_pos];
        word++;
        letter = *word;
    }

    // checks whether the node is terminal
    if (check_ptr->is_word)
    {
        return true;
    }

    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    char c;
    int buf_ctr = 0; //access control for buffer
    char buf[LENGTH+1] = { '\n' }; //empty buffer

    // for (int i = 0; i<LENGTH+1; i++)
    // {
    //     buf[i] = '\n';
    // }

    //open dictionary file
    FILE *dict_f_ptr = fopen(dictionary, "r");

    //error check for dictionary
    if (dict_f_ptr == NULL)
    {
        fclose(dict_f_ptr);
        return false;
    }

    //iterate the file until EOF
    while ((c = fgetc(dict_f_ptr)) != EOF)
    {
        //for lines longer than 45 letters
        if (buf_ctr >= LENGTH)
        {
            //add 45 letters to the dictionary
            add_word(buf);

            // scrap the rest of the line (needs EOF, if only one word in dict)
            while ((c = fgetc(dict_f_ptr)) != '\n' && c != '\0' && c != EOF);

            //reset access and start at next line
            buf_ctr = 0;
            continue;
        }

        // not end of line (or file)
        if (c != '\n' && c != '\0')
        {
            // add letter to buf
            buf[buf_ctr] = c;
        }

        // end of line
        else
        {

            //add terminator to the end of string
            buf[buf_ctr] = '\0';

            //add word to dictionary
            add_word(buf);

            // reset access
            buf_ctr = 0;
            continue;
        }

        //increment access
        buf_ctr++;
    }

    //close file
    fclose(dict_f_ptr);
    return true;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int size(void)
{
    // totally not cheating!!!!
    return words_in_dict;
}
/*
Checks all the pointers in a node, if all are NULL, frees the memory,
else goes deepah into the tree.
*/


bool clear_node (_entry * node)
{
    // check all pointers
    for (int i = 0; i < 26; i++)
    {
        //if pointer not NULL, follow it and deallocate that node
        if (node->entry_arr[i] != NULL)
        {
            //dreaded recursion
            clear_node(node->entry_arr[i]);
            //after all children cleared, set pointer to NULL
            node->entry_arr[i] = NULL;
        }
    }

    // zero node is initialized beforehand, don't need and can't deallocate
    if (node != &zero_node)
    {
        free(node);
    }

    return true;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //start clearing the node from the zero node
    bool cleared = clear_node(&zero_node);

    //inform about success
    return cleared;
}
