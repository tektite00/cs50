"""
Implements a python program that censors messages that contain words that appear on a list of supplied "banned words."

USAGE:
-----

```
$ python bleep.py banned.txt
What message would you like to censor?
What the heck
What the ****

```
$ python bleep.py banned.txt
What message would you like to censor?
gosh darn it
**** **** it
```
"""


import os
import sys


def main():

    # Throw error if wrong arguments passed
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    # Extract file path
    fpath = sys.argv[1]

    # Check if file path or file is valid
    if not os.path.isfile(sys.argv[1]):
        print(f"Invalid file path: {fpath}")
        sys.exit(1)

    # 1. Read in banned words file
    banned_words = set()
    with open(fpath) as fr:
        for line in fr:
            line = line.rstrip()
            banned_words.add(line)

    # 2. Get message from user to censor that contains banned words,
    # supplied by "banned.txt"
    while True:
        uncensored_message = input(
            "What message you would like to censor?\n")
        if uncensored_message:
            break

    # 3. Split the message into individual words
    words = uncensored_message.split()
    censored_message = []  # Stores censored message
    # 4. Loop through words and bleep the banned words
    for word in words:
        if word.lower() in banned_words:
            censored_message.append("*"*len(word))
            continue
        censored_message.append(word)
    # 5. Print censored message
    print(" ".join(censored_message))


if __name__ == "__main__":
    main()
