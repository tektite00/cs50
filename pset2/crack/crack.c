#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <crypt.h>
#include <time.h>

/**
 * TEST CASES
 *
 * CS50 2018 - crack.c
 * anushree:50xcIMJ0y.RXo - YES
 * brian:50mjprEcqC/ts - CA
 * bjbrown:50GApilQSG3E2 - UPenn
 * lloyd:50n0AAUD.pL8g - lloyd
 * malan:50CcfIk1QrPr6 - maybe
 * maria:509nVI8B9VfuA - TF
 * natmelo:50JIIyhDORqMU - nope
 * rob:50JGnXUgaafgc - ROFL
 * stelios:51u8F0dkeDSbY - NO
 * zamyla:50cI2vYkF0YU2 - LOL
 *
 * CS50 2019 - crack.c
 * brian:51.xJagtPnb6s - TF
 * bjbrown:50GApilQSG3E2 - UPenn
 * emc:502sDZxA/ybHs
 * greg:50C6B0oz0HWzo
 * jana:50WUNAFdX/yjA
 * lloyd:50n0AAUD.pL8g
 * malan:50CcfIk1QrPr6
 * natmelo:50JIIyhDORqMU
 * rob:51v3Nh6ZWGHOQ
 * veronica:61v1CDwwP95bY
 * walker:508ny6Rw0aRio
 * zamyla:50cI2vYkF0YU2
**/

/**
* Program cracks DES bases encryption, using C function crypt)
* Version: 1.0
*   - Added Brute Force Attack
*     Limitations:
*       - Password can be no longer than 5 characters long
*       - Password cannot contain numbers or special characters
*
**/

// Declare function prototypes
bool brute_force_attack(char* hash, char* salt);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // Get hashed password
    char* hash = argv[1];

    // Get Salt
    char salt[3];
    strncpy(salt, hash, 2);
    salt[2] = '\0';
//    eprintf("[DEBUG] Salt is: %s\n", salt);

    int seconds;
    seconds = time(NULL);
    printf("***************************************\n");

    printf("Trying out: BRUTE FORCE ATTACK\n");
    brute_force_attack(hash, salt);
    printf("***************************************\n");
    printf("Execution time: %d seconds\n", (int) time(NULL) - seconds);

    // Exit program
    return 0;
}



bool brute_force_attack(char* hash, char* salt)
{
    // ASCII Letters to loop over
    char* ascii_letter = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // char* ascii_letter ="\0etaoinshrdlcumwfgypbvkjxqzETAOINSHRDLCUMWFGYPBVKJXQZ";
    // char* ascii_letter ="\0ETAOINSHRDLCUMWFGYPBVKJXQZetaoinshrdlcumwfgypbvkjxqz";
    // char* ascii_letter= "\0eEtTaAoOiInNsShHrRdDlLcCuUmMwWfFgGyYpPbBvVkKjJxXqQzZ";
    const int letter_len = 53; // ASCII letter length size
//    eprintf("[DEBUG] ASCII letters length: %d\n", letter_len);

    /** Loop through all possible permutations for password.
    * E.g.:
    * guess[0] = 'T'
    * guess[1] = 'F'
    * guess[2] = '\0'
    * guess[3] = '\0'
    * guess[4] = '\0'
    *
    * Now, imagine the innermost loops goes over entire 52 ASCII chars,
    * than repaated by outer innermost loop over guess[1].
    *
    * Which gives you approx. permuatations:
    * 52 + 52^2 + 52^3 + 52^4 + 52^5
    **/

    // Create empry char array to hold guess password
    char guess[6] = "\0\0\0\0\0\0";

    for (int i = 0; i < letter_len; i++)
    {
        guess[4] = ascii_letter[i];
        for (int j = 0; j < letter_len; j++)
        {
            guess[3] = ascii_letter[j];
            for (int k = 0; k < letter_len; k++)
            {
                guess[2] = ascii_letter[k];
                for (int l = 0; l < letter_len; l++)
                {
                    guess[1] = ascii_letter[l];
                    for(int m = 0; m < letter_len; m++)
                    {

                        guess[0] = ascii_letter[m];
                        if (strcmp(crypt(guess, salt), hash) == 0)
                        {
                            printf("Password is: %s\n", guess);
                            return true;
                        }
                    }
                }
            }
        }
    }

    printf("Password couldn't be cracked");
    return false;

}