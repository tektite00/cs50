#### Implements a program that encrypts messages using Vigenère’s cipher.

```
$ ./vigenere ABC
plaintext:  HELLO
ciphertext: HFNLP
```

> NOTE:
> If **keyword** is single letter `'A'` or `'B'`, etc.., than it encrypts just like
> Caesar's cipher.

### Usage

Your program should behave per the examples below. Assumed that the underlined text is what some user has typed.


```
$ ./vigenere 13
Usage: ./vigenere k
```

```
$ ./vigenere
Usage: ./vigenere k
```

```
$ ./vigenere bacon and eggs
Usage: ./vigenere k
```
```
$ ./vigenere bacon
plaintext: Meet me at the park at eleven am
ciphertext: Negh zf av huf pcfx bt gzrwep oz
```

#### For more info: [docs](https://docs.cs50.net/2018/x/psets/2/vigenere/vigenere.html)
