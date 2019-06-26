"""
cash.py is python program that calculates the minimum number of coins required
to give a user change, contrast it with cash.c implementation.

USAGE:
```
$ python cash.py
Change owed: 0.41
4

$ python cash.py
Change owed: -0.41
Change owed: -0.41
Change owed: foo
Change owed: 0.41
4

```
"""
from cs50 import get_float


def main():

    # Prompt user for change
    while True:
        change = get_float("Change owed: ")
        change = int(round(change * 100))

        # Check input is valid, break out if it is
        if change > 0:
            break

    print("Change is: ", change)

    # Currency dictionary where values are in pennies
    currency = {
        "quarter": 25,
        "dime": 10,
        "nickle": 5,
        "penny": 1
    }

    # No. of coins
    coins = 0
    # Loop greedily beginning
    for key in currency:
        coins += change // currency[key]
        change %= currency[key]

    # Print no. of coins
    print(f"{coins}")


if __name__ == "__main__":
    main()
