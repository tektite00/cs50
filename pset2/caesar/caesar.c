#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * This program implements Caesar's cipher, by shifting each letter
 * by some number (key) of places.
 *
 * USAGE:
 * ./caesar <numeric key>
 * plaintext: <text>
 * ciphertext: <encrypted text>
 *
 **/

// Declare functions here
int get_ascii_offset(char c);
bool is_key_valid(string key);


// BEGIN MAIN
int main(int argc, string argv[])
{

    // 1. Get the key

    // a) Validate number of CLI arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar <key>\n");
        return 1;

    }

    // b) Check if key is valid numeric value.
    if (!is_key_valid(argv[1]))
    {
        printf("Key has to be integer value.\n");
        return 1;
    }

    // Convert key to integer.
    // If key is >= 26 wrap around, using mod 26
    int key = atoi(argv[1]) % 26;

    // 2. Get the plain text
    string plain_text = get_string("plaintext: ");

    // 3. Encipher
    // 4. Print cipher
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        // a) Check if char is alphabet character or not
        //    If not than continue
        if (!isalpha(plain_text[i]))
        {
            printf("%c", plain_text[i]);
            continue;
        }
        // If char is alphabet
        // b) Check if it is UPPERCASE or lowercase and assign
        // appropriate ASCII offset
        int ascii_offset = get_ascii_offset(plain_text[i]);

        // c) Encipher the plain_text char
        int offset_char = plain_text[i] - ascii_offset;
        offset_char = (offset_char + key) % 26;
        int encrypted_char = offset_char + ascii_offset;
        printf("%c", encrypted_char);
    }

    printf("\n"); // Adds new line
    return 0; // All went well, return success


}
// END MAIN

/**
 * Function cheks whether string key is valid integer value or not.
 * INPUT: string key
 * OUTPUT: true or false
 **/
bool is_key_valid(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isdigit(key[i]))
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