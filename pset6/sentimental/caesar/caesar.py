"""
caesar.py is python program that encrypts messages using Caesar’s cipher, contrast it with caesar.c implementation.

CORRECT USAGE:

```
$ python caesar.py 13
plaintext:  hello, world
ciphertext: uryyb, jbeyq
```

```
$ python caesar.py 13
plaintext:  HELLO
ciphertext: URYYB
```

```
$ python caesar.py 13
plaintext:  be sure to drink your Ovaltine
ciphertext: or fher gb qevax lbhe Binygvar
```
INCORRECT USAGE:
```
$ python caesar.py 1 2 3 4 5
Usage: python caesar.py k
```
"""

import sys


def get_ascii_offset(char):
    """
    Function returns ascii offset for upper or lower case character.
    """
    return 65 if char.isupper() else 97


def cipher_char(char, key):
    """
    Function encrypts ASCII upper and lower case char, based on
    integer key provided.
    """
    # Get ASCII offset based on if char is UPPER case or lower case
    ascii_offset = get_ascii_offset(char)
    char_idx = ord(char) - ascii_offset
    trans_char = (char_idx + key) % 26
    char = chr(trans_char + ascii_offset)
    return char


def caesar(text, key, mode):
    """
    Function that implements Caesar’s algorithm (i.e., cipher) encrypts messages by “rotating” each letter by k positions.
    More formally:
        - if p is some plaintext (i.e., an unencrypted message)
        - pi is the ith character in p,
        - and k is a secret key (i.e., a non-negative integer),
    then each letter, ci, in the ciphertext, c, is computed as:
        ci = (pi + k) % 26
    """
    # Check if mode is to decrypt
    if mode == 'd':
        key *= -1  # flips key sign

    trans_txt = ""  # stores translated text

    # loop through each character in text
    for char in text:
        # a) Check if char is alphabet character or not
        #    if not than continue
        if not char.isalpha():
            trans_txt += char
            continue
        # b) else char is alphabet
        #    decrypt or encrypt it based on mode
        trans_txt += cipher_char(char, key)

    # return translated text
    return trans_txt


def main():
    # 1. Parse arguments
    argc = len(sys.argv)  # argument length
    if argc != 2 and argc != 3:
        exit("Usage: python caesar.py [mode] key")

    # 2. Check if the mode is valid to encrypt or decrypt
    mode = sys.argv[1].lower() if argc == 3 else 'e'
    if not mode in 'encrypt e decrypt d'.split():
        exit("Usage: [mode] - either 'encrypt' or 'e' or 'decrypt' or 'd'.")
    if len(mode) > 1:
        mode = mode[0]

    # 3. Check if the key is valid numeric digits
    key = sys.argv[2] if argc == 3 else sys.argv[1]
    if not key.isdigit():
        exit("Usage: key - Key has to be numeric digits.")

    # 4. Convert key to integer and,
    # if key is >= 26 wrap around, using mod 26
    key = int(float(key)) % 26

    # 5. Translate text, depending on mode:

    # 5a) if mode == 'decrypt' or 'd' text is decrypted
    # Prompt user for plain text
    if mode == "d":
        cipher_txt = input("ciphertext: ")
        translated_txt = caesar(cipher_txt, key, mode)
        print("plaintext: ", translated_txt)

    # 5b) else mode == 'encrypt' or 'e', text is encrypted
    else:
        plain_txt = input("plaintext: ")
        translated_txt = caesar(plain_txt, key, mode)
        print("ciphertext: ", translated_txt)


if __name__ == "__main__":
    main()
