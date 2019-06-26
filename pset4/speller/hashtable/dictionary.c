// Implements a dictionary's functionality
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
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

// Represents a hash table
node *hashtable[N];



// Hashes word to a number between 0 and 25, inclusive, based on its first letter
// unsigned int naive_hash(const char *word)
// {
//     return tolower(word[0]) - 'a';
// }

// djb2 hash from: http://www.cse.yorku.ca/~oz/hash.html
unsigned long djb2_hash(const char *word)
{
    unsigned long hash = 5381;
    int ch;
    while ((ch = *word++))
    {
        // hash * 33 + ch
        hash = ((hash << 5) + hash) + ch;
    }
    return hash;
}


// Keeps track of no. of words in dictionary
unsigned long count_dict_words = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char sword[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", sword) != EOF)
    {
        // Create new node and check if it succeeds
        node *word_node = malloc(sizeof(node));
        if (word_node == NULL)
        {
            unload();
            return false;
        }
        // Copy word into a new node
        strcpy(word_node -> word, sword);
        // Get hashlocation in array
        unsigned long loc = djb2_hash(sword) % N;
        word_node -> next = hashtable[loc];
        hashtable[loc] = word_node;
        count_dict_words++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count_dict_words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create char array to store copy of word, since we
    // can't change const char *word
    int n = strlen(word);
    char word_copy[n + 1];
    for (int i = 0; i < n; i ++)
    {
        word_copy[i] = tolower(word[i]);
    }
    // Add null terminator
    word_copy[n] = '\0';

    // Get hash location and
    // Get head ndoe in the hashtable
    node *cursor = hashtable[djb2_hash(word_copy) % N];

    // Loop through linked list
    while (cursor != NULL)
    {
        // Compare string
        if (strcmp(cursor->word, word_copy) == 0)
        {
            // If similar return true
            return true;
        }
        cursor = cursor -> next;
    }
    // After exahusting dictionary no words were found
    // so return false
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // Get head node from hash table
        node *cursor = hashtable[i];

        // While cursor traverses linked list
        while (cursor != NULL)
        {
            // Get current node to temp
            node *temp = cursor;
            // Point cursor to next node
            cursor = cursor -> next;
            // Free the temp node
            free(temp);
        }

    }
    return true;
}
