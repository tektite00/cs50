// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Represents number of buckets in a hash table
// #define N 76801
//#define N 85000
//#define N 90000
//#define N 100000
//#define N 110000
//#define N 120000
//#define N 130000
//#define N 140000
//#define N 150000
#define N 200000


// Prototypes
bool load(const char *dictionary);
unsigned int size(void);
bool check(const char *word);
bool unload(void);

#endif // DICTIONARY_H
