// Helper functions for music

#include <cs50.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';
    return (numerator * (8 / denominator));
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Get the octave
    int octave = note[strlen(note) - 1] - '0';

    // Base frequency for A4 ~ 440Hx
    float a4_freq = 440.0;

    // Holds difference of semi-tones from base A4
    int diff = 0;

    //eprintf("letter : %c\n", note[0]);
    //eprintf("octave : %d\n", octave);

    // 1) Adjust semi-tone for A - G letters
    switch (note[0])
    {
        case 'C':
            diff -= 9;
            break;
        case 'D':
            diff -= 7;
            break;
        case 'E':
            diff -= 5;
            break;
        case 'F':
            diff -= 4;
            break;
        case 'G':
            diff -= 2;
            break;
        case 'A':
            break;
        case 'B':
            diff += 2;
            break;
    }

    //eprintf("leters adjusted diff : %d\n", diff);

    // 2) Adjust for accidentals
    if (strlen(note) == 3)
    {
        if (note[1] == '#')
        {
            diff += 1;
        }
        else if (note[1] == 'b')
        {
            diff -= 1;
        }
    }

    //eprintf("accidentals adjusted diff : %d\n", diff);

    // 3) Adjust for octave
    diff += (octave - 4) * 12;

    //eprintf("octave adjusted diff : %d\n", diff);

    // 4) Compute & return frequency
    float freq = pow(2.0, diff / 12.0) * a4_freq;

    return round(freq);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) != 0)
    {
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            if (!isspace(s[i]))
            {
                return false;
            }
        }
    }
    return true;
}
