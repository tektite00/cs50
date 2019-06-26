"""
mario.py (more) is python program that double half-pyramid of a specified height
contrast it with mario.c (more) implementation.

USAGE:
```
$ python mario.py
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
```
"""

from cs50 import get_int


def draw(ctype, times):
    """
    draw(ctype, times)
        input:
            ctype - char or string to draw
            times - no. of times to draw them
        output:
            prints type n times with no "\n" appended at the end
    """
    print(ctype * times, end="")


def main():

    # Mimicks do-while loop in C
    # Prompt the user for height
    while True:
        height = get_int("Height: ")
        if (height >= 1 and height <= 8):
            break

    # Determines type of mario half-pyramid
    nhash = 1

    # Draws half-pyramid of specified height
    for i in range(height):
        # 1. print spaces
        draw(" ", height - 1 - i)
        # 2. print hashes
        draw("#", nhash + i)
        # 3. print gap
        draw(" ", 2)
        # 4. print right pyramid
        draw("#", nhash + i)
        # 5. finally at end of row, print newline
        print()


if __name__ == "__main__":
    main()
