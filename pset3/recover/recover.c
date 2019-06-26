#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Designate block size
#define BLOCK_SIZE 512

// Similar to "bmp.h"
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover raw_file\n");
        return 1;
    }


    char *infile = argv[1];

    // 1. Open memory card file, and ensure we didn't get NULL back
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open RAW_FILE: %s.\n", infile);
        return 2;
    }

    // Declare Char Array to hold recovered JPEG filename
    char filename[8];

    // Declare outfile ptr
    FILE *outptr = NULL;

    // Bytes Array to holde defined BLOCK_SIZE
    BYTE buffer[BLOCK_SIZE];

    // Counter for jpegs found
    int img_counter = 0;

    // 2. Read 512 bytes into buffer, and repeat until end of card
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // 3. Determine if the first 4 bytes are start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // 4. Since we found a new JPEG, close the previous JPEG file
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // 5. Assign a name, and ooen new JPEG file to write
            sprintf(filename, "%03i.jpg", img_counter++);
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not open JPEG: %s.\n", filename);
                return 3;
            }
        }

        // 6. If JPEG is open, keep writing the blocks
        if (outptr != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }

    }

    // Close in and outfile ptrs.
    fclose(inptr);
    fclose(outptr);

    // Return Sucess
    return 0;
}
