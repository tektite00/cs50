#include<stdio.h>
#include<cs50.h>
#include<math.h>


int main(void)
{
    // Declare vars and constants here
    float change;
    int quarter = 25;
    int dime = 10;
    int nickle = 5;
    int penny = 1;
    do
    {
        change = get_float("Change owed: ");
        change *= 100;
        change = round(change);
    }
    while (change <= 0);
    // eprintf("Rounded change is: %f\n", change);


    int qcount = change / quarter;
    change = change - (quarter * qcount);

    int dcount = change / dime;
    change = change - (dime * dcount);

    int ncount = change / nickle;
    change = change - (nickle * ncount);

    int pcount = change / penny;
    change = change - (penny * pcount);

    // eprintf("Quarter count is: %d\n", qcount);
    // eprintf("Dime count is: %d\n", dcount);
    // eprintf("Nickle count is: %d\n", ncount);
    // eprintf("Penny count is: %d\n", pcount);

    printf("%d\n", (qcount + dcount + ncount + pcount));


}