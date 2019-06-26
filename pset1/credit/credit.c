#include<stdio.h>
#include<cs50.h>
#include<math.h>

/**
 * This program determines whether a provided card number is valid according to Luhn's algorithm.
 **/

int main()
{
    // 1. Get credit card number from user which is positive
    long cc_num;
    do
    {
        cc_num = get_long("Credit Card Number: ");
    }
    while (cc_num <= 0);

    // 2. Validate Credit Card number using Luhn's algorithm
    /**
     * a) Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.
     * b) Add the sum to the sum of the digits that weren’t multiplied by 2.
     * c) If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    **/
    // 3. If card is valid, determine type of card by issuer company identifiers
    /**
     * AMEX: Count - 15 digits, Starts with 34, 37
     * MASTERCARD: Count - 16 digits, Starts with 51, 52, 53, 54, 55
     * VISA: Count - 13 or 16, Starts with 4
     **/

    // Declare vars needed for Luhn's algorithm
    int num_digits = 0;
    int sum_even = 0;
    int sum_odd = 0;
    int last_digit = 0;
    int prev_last_digit = 0;
    int total;

    // Logic for CC checking
    while (cc_num > 0)
    {

        num_digits++; // Counter for CC length
        // eprintf("num_digits: %d\n", num_digits);

        prev_last_digit = last_digit; // store previous last digit
        last_digit = cc_num % 10; // computes last digit

        // eprintf("last_digit: %d\n", last_digit);
        // eprintf("prev_last_digit: %d\n", prev_last_digit);

        if (num_digits % 2 == 0)
        {
            int product = 2 * last_digit;
            sum_even += (product % 10) + (product / 10);
            // eprintf("sum_even: %d\n", sum_even);
        }
        else
        {
            sum_odd += last_digit;
            // eprintf("sum_odd: %d\n", sum_odd);
        }
        cc_num /= 10;
        // eprintf("new cc_num: %li\n", cc_num);


    }

    // Compute total sum that,
    // should be divisible by 10 to be valid CC number.
    total = sum_even + sum_odd;
    // eprintf("total: %d\n", total);

    // Get first two digits
    int digits = (last_digit * 10) + prev_last_digit;
    // eprintf("CC Numbers first_two_digit %d\n", digits);

    // Logic for figuring out CC Issuer Name
    if ((total % 10) == 0)
    {
        if ((digits == 34 || digits == 37) && num_digits == 15)
        {
            printf("AMEX\n");
        }
        else if ((digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55) && num_digits == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (last_digit == 4 && (num_digits == 13 || num_digits == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
