# Questions

## What's `stdint.h`?

`stdint.h` is a header file for instroducing more integer datatypes which allows to be more precise as to what width the datatype
can be, for example, integer can be unsigned, signed with size of width 8 bits, 16, 32, and maximum up to 64 bits.


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

This are the C/C++ aliases of primitive data types that map to data types used in Windows programming like `BYTE`, `DWORD`, `LONG`, and `WORD`.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

- `BYTE`:  1 byte
- `DWORD`: 4 bytes
- `LONG`: 4 bytes
- `WORD`:  2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

First two bytes are: `0x4d42`.

## What's the difference between `bfSize` and `biSize`?

`bfSize` is total size of FILE in bytes, whereas `biSize` is total number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

If `biHeight` is positive, the bitmap is a bottom-up DIB and its origin is the lower-left corner.
If `biHeight` is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` (number of bits-per-pixel) field in the `BITMAPINFOHEADER` struct determines the number of bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

`fopen` can return `NULL` if OS cannot open the file with given permission and type of mode, or filepath is invalid,
or file is write-protected, in those cases `fopen` will return the `NULL` pointer.

## Why is the third argument to `fread` always `1` in our code?

Because there's only one file and info header, and we read and write one RGBTRIPLE at a time.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

$$
padding\ &=\ (4\ -\ (bi.biWidth\ *\ sizeof(RGBTRIPLE))\ \%\ 4)\ \%\ 4 \\
&=\ (4\ -\ (3\ *\ 3)\ \%\ 4)\ \%\ 4 \\
&=\ 3\ \%\ 4 \\
$$

## What does `fseek` do?

`fseek` is file position indicator which jumps over to offset specified from
designated position - i.e. current position, beginning of file or end of file.

## What is `SEEK_CUR`?

- `SEEK_CUR` : is the current position in file.

## Whodunit?

It was Professor Plum with the Candlestick in the library.
