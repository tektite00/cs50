// Copies a BMP file
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // convert string to float type
    // f - is scale factor
    float f = atof(argv[1]);

    if (f <= 0 || f > 100)
    {
        fprintf(stderr, "f has to be float between (0.0, 100] %s\n", argv[1]);
        return 2;
    }

    // printf("n is %d\n", n);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Assign infile dimensions
    int inWidth = bi.biWidth;
    int inHeight = bi.biHeight;

    // Update outfile's dimensions
    // Looked to me Staff solution used floor
    // Thus using floor, but round would be better choice
    int outWidth = floor(inWidth * f);
    int outHeight = ceil(inHeight * f); // Since, height is negative

    // determine padding for scanlines
    int inpadding = (4 - (inWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding = (4 - (outWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Update FILE & INFO HEADERS
    bi.biWidth = outWidth;
    bi.biHeight = outHeight;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * outWidth) + outpadding) * abs(outHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // ----------"RE-WRITE" Method ----------

    // allocate memory for outfile RGB triple array
    RGBTRIPLE *outScanline = malloc(outWidth * sizeof(RGBTRIPLE));

    int n;
    if (f > 1) // Enlarges
    {
        n = ceil(f); // Or floor(f) + 1
    }
    else // Shrinks
    {
        n = (int) 1 / f;
    }

    int scanline_row = 0; // iterates over scan line row

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inHeight); i < biHeight; i++)
    {

        int scanline_col = 0; // iterates over scanline column
        printf("Storing Col #: \n");
        for (int j = 0; j < inWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (f < 1) // Shrinks
            {
                if (j % n == 0 && scanline_col < outWidth)
                {
                    printf("%d", scanline_col);
                    outScanline[scanline_col++] = triple;
                }
            }
            else // Enlarges
            {
                // remember pixels in outScanline array
                for (int k = 0; k < n && scanline_col < outWidth; k++)
                {
                    printf("%d", scanline_col);
                    outScanline[scanline_col++] = triple;
                }
            }

        }
        printf("\n");

        if (f < 1)
        {
            if (i % n == 0 && scanline_row < abs(outHeight))
            {
                // write new RGB triple array scanline to outfile
                fwrite(outScanline, sizeof(RGBTRIPLE), outWidth, outptr);
                printf("Writing Row #: %d\n", scanline_row);
                scanline_row++;

                // write outfile padding
                for (int k = 0; k < outpadding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        else
        {
            // write RGB triple scanline array as many times as n
            for (int m = 0; m < n && scanline_row < abs(outHeight); m++)
            {
                // write new RGB triple array scanline to outfile
                fwrite(outScanline, sizeof(RGBTRIPLE), outWidth, outptr);
                printf("Writing Row #: %d\n", scanline_row);
                scanline_row++;

                // write outfile padding
                for (int k = 0; k < outpadding; k++)
                {
                    fputc(0x00, outptr);
                }

            }
        }

        // skip over padding, if any
        fseek(inptr, inpadding, SEEK_CUR);

    }
    // free memory
    free(outScanline);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
