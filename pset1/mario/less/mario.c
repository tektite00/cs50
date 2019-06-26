#include<stdio.h>
#include<cs50.h>

void draw(char type, int times)
{
    for (int i = 0; i < times; i++)
    {
        printf("%c", type);
    }
}

// Program draws half-pyramids
int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");

    }
    while (height < 0 || height > 23);

    int nhash = 1;
    // prints left pyramid
    for (int i = 0; i < height; i++)
    {
        draw(' ', height - 1 -i); // draw spaces
        draw('#', nhash + i); // draws hash
        printf("\n"); // prints newline
    }
}
