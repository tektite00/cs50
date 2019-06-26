"""
vigenere.py is python program that encrypts messages using Vigenère’s cipher, which improves upon
Caesar's cipher, by encrypting messages using a sequence of keys, from a keyword.
Contrast it with vigenere.c implementation.

CORRECT USAGE:

```
$ python vigenere.py bacon
plaintext: Meet me at the park at eleven am
ciphertext: Negh zf av huf pcfx bt gzrwep oz
```

```
$ python vigenere.py ABC
plaintext:  HELLO
ciphertext: HFNLP
```

INCORRECT USAGE:
```
$ python vigenere.py bacon and eggs
Usage: python vigenere.py k
```

```
$ python vigenere.py bacon and eggs
Usage: python vigenere.py k
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


def vigenere(text, keyword, mode):
    """
    Function that implements Vigenère’s algorithm (i.e., cipher) improves upon Caesar's cipher by encrypting
    messages using a sequence of keys (or, put another way, a keyword)

    So,
        - if p is some plaintext (i.e., an unencrypted message)
        - pi is the ith character in p,
        - and kj is a letter in keyword, which is rotated cyclically
            if k is shorter than p, as many times as it takes to encrypt p

    then each letter, ci, in the ciphertext, c, is computed as:
        for kj in keword:
            ci = (pi + kj) % 26
    """
    trans_txt = ""              # stores translated text
    key_index = 0               # counter for keword
    keyword_len = len(keyword)  # keyword length

    # loop through each character in text
    for char in text:
        # a) Check if char is alphabet character or not
        #    if not than continue
        if not char.isalpha():
            trans_txt += char
            continue

        # b) else char is alphabet
        # loop cyclically through keword using
        # key_index
        key_char = keyword[key_index % keyword_len]
        key_index += 1
        # get ASCII offset for UPPER or lower case letter
        # in keyword
        ascii_offset = get_ascii_offset(key_char)
        # convert keyword to integer and subtract
        # ASCII offset
        key = ord(key_char) - ascii_offset
        # check if mode is to decrypt
        if mode == 'd':
            key *= -1  # flips key sign
        trans_txt += cipher_char(char, key)

    # return translated text
    return trans_txt


def main():
    # 1. Parse arguments
    argc = len(sys.argv)  # argument length
    if argc != 2 and argc != 3:
        exit("Usage: python vigenere.py [mode] keyword")

    # 2. Check if the mode is valid to encrypt or decrypt
    mode = sys.argv[1].lower() if argc == 3 else 'e'
    if not mode in 'encrypt e decrypt d'.split():
        exit("Usage: [mode] - either 'encrypt' or 'e' or 'decrypt' or 'd'.")
    if len(mode) > 1:
        mode = mode[0]

    # 3. Check if the keyword is valid sequence of alphabetic letters
    keyword = sys.argv[2] if argc == 3 else sys.argv[1]
    if not keyword.isalpha():
        exit("Usage: keyword - Keyword has to composed entirely of alphabetical characters.")

    # 4. Translate text, depending on mode:

    # 4a) if mode == 'decrypt' or 'd' text is decrypted
    # Prompt user for plain text
    if mode == "d":
        cipher_txt = input("ciphertext: ")
        translated_txt = vigenere(cipher_txt, keyword, mode)
        print("plaintext: ", translated_txt)

    # 4b) else mode == 'encrypt' or 'e', text is encrypted
    else:
        plain_txt = input("plaintext: ")
        translated_txt = vigenere(plain_txt, keyword, mode)
        print("ciphertext: ", translated_txt)


if __name__ == "__main__":
    main()
