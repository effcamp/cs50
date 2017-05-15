/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node *children[27];
} node;

node *root;
int wordcount = 0;
int loaded = 0;


void deletenode(node* rootp)
{
    for (int i = 0; i < 27; i++)
        {
            if ((rootp->children[i]) != NULL)
                deletenode(rootp->children[i]);
        }
    free(rootp);
}



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    node* trav = root;
    int len = strlen(word);
    int index;
    for (int i = 0; i < len; i++)
    {
        index = (tolower(word[i])-'a');
        
        if (word[i] == '\'')
            index = 26;
        
        
        if (trav->children[index] != NULL)
            trav = trav->children[index];
        else
            return false;
    }
    
    if (trav->is_word == true)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    root = calloc(1, sizeof(node));
    node *trav = root;
    int index;
    char tmp;
    
    while ((tmp = fgetc(dict)) != EOF)
    {
        index = tmp - 'a';
        if (tmp == '\'')
            index = 26;
            
        if (tmp == '\n')
        {
            // set bool to true
            trav->is_word = true;
            wordcount++;
            trav = root;
        }
        else 
        {
            if (trav->children[index] == NULL)
            {
                trav->children[index] = calloc(1, sizeof(node));
                if (trav->children[index] == NULL)
                {
                    unload();
                    return false;
                }
                trav = trav->children[index];
            }
            else
            {
                trav = trav->children[index];
            }
        }
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    deletenode(root);
    return true;
}
