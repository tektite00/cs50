 #include<stdio.h>
#include<cs50.h>
#include<math.h>


int main(void)

{
    float change;

    do
    {
        change = get_float("Change owed: ");
        change = round(change * 100);
    }
    while (change <= 0);


    int qcount = 0;
    int dcount = 0;
    int ncount = 0;
    int pcount = 0;

    while (change >= 25)
    {
        change -= 25;
        qcount++;
    }
    eprintf("Quarter count is: %d\n", qcount);

    while (change >= 10)
    {
        change -= 10;
        dcount++;
    }
    eprintf("Dime count is: %d\n", dcount);

    while (change >= 5)
    {
        change -= 5;
        ncount++;
    }
    eprintf("Nickle count is: %d\n", ncount);

    while (change >= 1)
    {
        change -= 1;
        pcount++;
    }
    eprintf("Penny count is: %d\n", pcount);

    printf("%d\n", (qcount + dcount + ncount + pcount));

}