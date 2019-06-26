#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * This program implements Vigenere's cipher which improves upon
 * Caesar's cipher, by encrypting messages using a sequence of keys,
 * from a keyword.
 *
 * USAGE:
 * $./vigenere <input string keyword i.e. non-numeric and special characters>
 * plaintext: <input text>
 * ciphertext: <outputs encrypted text>
 *
 **/


// Declare functions here
int get_ascii_offset(char c);
bool is_key_valid(string key);
char encipher_char(char c, int k);


// BEGIN MAIN
int main(int argc, string argv[])
{

    // 1. Get the keyword

    // a) Validate number of CLI arguments
    if (argc != 2)
    {
        printf("Usage: ./vigenere <keyword>\n");
        return 1;

    }

    // b) Check if keyword is valid non-numeric alphabet keyword.
    if (!is_key_valid(argv[1]))
    {
        printf("Keyword has to be non-numeric alphabet keyword.\n");
        return 1;
    }

    // Store keyword in var keyword
    string keyword = argv[1];

    // 2. Get the plain text
    string plain_text = get_string("plaintext: ");


    printf("ciphertext: ");
    int j = 0;
    int keyword_len = strlen(keyword);

    // 3. Encipher
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        // a) Check if char is alphabet character or not
        //    If not than continue
        if (!isalpha(plain_text[i]))
        {
            printf("%c", plain_text[i]);
            continue;
        }

        // b) Encipher the plain_text char
        char key_char = keyword[j++ % keyword_len];
        int ascii_offset = get_ascii_offset(key_char);
        int key = key_char - ascii_offset;
        char c = encipher_char(plain_text[i], key);
        printf("%c", c);
    }

    printf("\n"); // Adds new line
    return 0; // All went well, return success


}
// END MAIN

/**
 * Function encrypts ASCII char, based on the integer key provided.
 * INPUT: char c, int k
 * OUPUT: return encrypted char c
 **/
char encipher_char(char c, int k)
{
    int ascii_offset = get_ascii_offset(c);
    int offset_char = c - ascii_offset;
    offset_char = (offset_char + k) % 26;
    c = (char) offset_char + ascii_offset;
    return c;
}


/**
 * Function cheks whether string key is valid keyword or not.
 * INPUT: string keyword
 * OUTPUT: true or false
 **/
bool is_key_valid(string keyword)
{
    for (int i = 0, n = strlen(keyword); i < n; i++)
    {
        if (!isalpha(keyword[i]))
        {
            return false;
        }
    }

    return true;

}

/**
 * Function returns ascii offset for upper or lower case character
 * INPUT: char c
 * OUTPUT: 65 for UPPER, and 97 for lower
 **/
int get_ascii_offset(char c)
{
    return isupper(c) ? 65 : 97;
}