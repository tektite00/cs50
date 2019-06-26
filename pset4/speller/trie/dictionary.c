// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie root node
node *root = NULL;

// Counter for number of words in a dictionary
unsigned int words_counter = 0;

// Returns index of the letter in children ptr array
unsigned int hash(char letter)
{
    // Assign last position to the apostrophe
    if (letter == '\'')
    {
        return N - 1;
    }
    // Ignores case by normalizing input to lower case
    return tolower(letter) - 97;
}

// Creates and Initializes new node to NULL
node *create_node(void)
{
    // Allocate memory for new node
    node *new_node = malloc(sizeof(node));
    // If insufficient memory
    if (new_node == NULL)
    {
        return NULL;
    }
    // Assign default values
    new_node -> is_word = false;

    // Initialize child pointers to NULL
    for (int i = 0; i < N; i++)
    {
        new_node -> children[i] = NULL;
    }

    return new_node;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Start from root node to traverse trie,
        // for each word in dictionary
        node *cursor = root;

        for (int i = 0, n = strlen(word); i < n; i++)
        {
            unsigned int index = hash(word[i]);

            // Create node if it's child pointer to NULL
            if (cursor -> children[index] == NULL)
            {
                cursor -> children[index] = create_node();
                // Can't allocate memory free other nodes and return false
                if (cursor -> children[index] == NULL)
                {
                    unload();
                    return false;
                }
            }
            // Go to that child node pointed by child pointer
            cursor = cursor -> children[index];
        }
        // At the end of the loop, we are at last letter in word
        cursor -> is_word = true;
        words_counter++;

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words_counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = root;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        unsigned int index = hash(word[i]);
        // Go to that corresponding child letter node in trie
        cursor = cursor -> children[index];
        if (cursor == NULL)
        {
            // Word is mispelled
            return false;
        }

    }
    // At the end of loop, we have reached end of word,
    // return true if is_word is true otherwise, false
    return cursor -> is_word;
}

bool free_nodes(node *cursor)
{
    // Loop through each node's children pointers
    for (int i = 0; i < N; i++)
    {
        // If child is not NULL, recurse to that node
        if (cursor -> children[i] != NULL)
        {
            free_nodes(cursor -> children[i]);
        }
        // else, ignore if is NULL
    }

    // If all child pointers are NULL, i.e. not pointing any other
    // node in trie than free that node.
    free(cursor);

    return true;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    return free_nodes(root);
}
