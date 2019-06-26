#include<stdio.h>
#include<cs50.h>

// Program draws mario's two half-pyramids

void draw(char type, int times)
{
    for (int i = 0; i < times; i++)
    {
        printf("%c", type);
    }
}


int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");

    }
    while (height < 0 || height > 23);

    int nhash = 2;

    // for each row
    for (int i = 0; i < height; i++)
    {
        // 1. print left pyramid
        // print spaces
        draw(' ', height - 1 - i);
        // print hashes
        draw('#', nhash + i);
        // 2. print gap
        draw(' ', 2);
        // 3. print right pyramid
        draw('#', nhash + i);
        // 4. end current line and increment nhash
        printf("\n");
    }
}