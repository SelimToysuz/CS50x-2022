// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

unsigned int DICTIONARY_SIZE;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor;

    cursor = table[hash(word)];
    if (cursor == NULL)
    {
        return false;
    }

    while (strcasecmp(word, cursor->word) != 0 && cursor->next != NULL)
    {
        cursor = cursor->next;
    }

    if (strcasecmp(word, cursor->word) != 0)
    {
        return false;
    }

    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int first, second, third;

    first = toupper(word[0]) - 'A';

    if (word[1] != '\0' && isalpha(word[1]))
    {
        second = toupper(word[1]) - 'A';
    }
    else
    {
        second = 0;
    }


    if (word[2] != '\0' && isalpha(word[2]))
    {
        third = toupper(word[2]) - 'A';
    }
    else
    {
        third = 0;
    }

    return (first * 676) + (second * 26) + third;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char *word = malloc(LENGTH + 1);
    if (word == NULL)
    {
        return false;
    }

    node *n;

    int i = 0;
    while (fscanf(file, "%s", word) != EOF)
    {
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        strcpy(n->word, word);
        unsigned int a = hash(n->word);

        n->next = table[a];
        table[a] = n;
        i++;
    }

    DICTIONARY_SIZE = i;

    free(word);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size()
{
    return DICTIONARY_SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor;
        node *tmp;
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }

    return true;
}
