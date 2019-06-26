"""
is python program that etermines whether a provided credit card number is valid
according to Luhn’s algorithm, contrast it with credit.c implementation.

USAGE:

$ python credit.py
Number: 378282246310005
AMEX

$ python credit.py
Number: 3782-822-463-10005
Number: foo
Number: 378282246310005
AMEX

$ python credit.py
Number: 6176292929
INVALID

"""


def main():

    # Get credit card number from user which is positive
    while True:
        cc_num = input("Credit Card Number: ")
        try:
            cc_num = int(cc_num)
            if cc_num > 0:  # Check if it is positive num
                break
        except ValueError:
            continue

    # 2. Validate Credit Card number using Luhn's algorithm
    """
    a)  Multiply every other digit by 2, starting with the number’s 
        second-to-last digit, and then add those products' digits together.
    b)  Add the sum to the sum of the digits that weren’t multiplied by 2.
    c)  If the total’s last digit is 0 (or, put more formally, if the 
        total modulo 10 is congruent to 0), the number is valid!
    """
    # Declare vars needed for Luhn's algorithm
    num_digits = 0
    sum_even = 0
    sum_odd = 0
    last_digit = 0
    prev_last_digit = 0
    total = 0

    # Logic for CC checking
    while cc_num > 0:

        num_digits += 1  # Counter for credit card length

        prev_last_digit = last_digit  # Stores previous last digit
        last_digit = cc_num % 10  # Gets last digit

        # If no. of digits are even, computes even sum
        if (num_digits % 2 == 0):
            product = 2 * last_digit
            sum_even += (product % 10) + (product // 10)

        # Else no. of digits are odd, computes odd sum
        else:
            sum_odd += last_digit

        # Removes last digit from Credit Card Number
        cc_num //= 10

    # Compute total sum (aka checksum), that should be divisible by 10 to be
    # valid Credit Card number
    total = sum_even + sum_odd

    # Gets first two digits
    digits = (last_digit * 10) + prev_last_digit

    # 3. If card is valid, determine type of card by issuer company identifiers
    """
         * AMEX: Count - 15 digits, Starts with 34, 37
         * MASTERCARD: Count - 16 digits, Starts with 51, 52, 53, 54, 55
         * VISA: Count - 13 or 16, Starts with 4
    """

    # Logic for checking Credit Card Issuer
    if total % 10 == 0:
        if (digits == 34 or digits == 37) and num_digits == 15:
            print("AMEX")
        elif (digits == 51 or digits == 52 or digits == 53 or digits == 54 or digits == 55) and num_digits == 16:
            print("MASTERCARD")
        elif last_digit == 4 and (num_digits == 13 or num_digits == 16):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
