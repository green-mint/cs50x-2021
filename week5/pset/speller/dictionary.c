// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 80;
unsigned int dictsize = 0;
bool loaded = false;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    
    unsigned int index = hash(word);
    node *current_bucket = table[index];
    
    char check_word[LENGTH + 1];
    strcpy(check_word, word);

    for (int i = 0; i < strlen(word); i += 1)
    {
        check_word[i] = tolower(check_word[i]);
    }
    
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(check_word,tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    
    while ((c = *word++)) // change
    {
        c = tolower(c);
        hash = hash * 33 + c;
    }
    
    hash = hash % N;
    
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    
    if (dict == NULL)
    {
        printf("Couldn't open file\n");
        return false;
    }
    
    char word[LENGTH + 2];
    
    while (fgets(word,LENGTH + 2,dict))
    {
        int word_len = strlen(word);
        
        if (word[word_len - 1] == '\n')
        {
            word[word_len - 1] = '\0';
        }
        
        unsigned int index = hash(word);
        node *current_bucket = table[index];
        
        node *n = malloc(sizeof(node));
        strcpy(n -> word,word); //change
        n -> next = NULL;
        
        if (current_bucket == NULL)
        {
            current_bucket = n;
        }
        
        else
        {
            node *temp = current_bucket;
            while (temp -> next != NULL)
            {
                temp = temp -> next;
            }
            
            temp -> next = n;
        }
        table[index] = current_bucket;
        dictsize++;
    }
    loaded = true;
    fclose(dict);
    return loaded;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return dictsize;
    }
    else
    {
        return 0;
    }
    
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *current, *prev;
    for (int i = 0; i < N; i += 1)
    {
        if (table[i] != NULL)
        {
            prev = table[i];
            current = prev->next;
            free(prev);

            while (current != NULL)
            {
                prev = current;
                current = current->next;
                free(prev);
            }
        }
    }
    return true;
}
