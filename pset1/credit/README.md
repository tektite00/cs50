####  Implements a program that determines whether a provided credit card number is valid according to Luhn’s algorithm.

```
$ ./credit
Number: 378282246310005
AMEX
```

### Usage

Program should behave per the example below.

Identifies following merchant:
- AMEX
- VISA
- MASTERCARD

```
$ ./credit
Number: 378282246310005
AMEX
```
```
$ ./credit
Number: 3782-822-463-10005
Number: foo
Number: 378282246310005
AMEX
```
```
$ ./credit
Number: 6176292929
INVALID
```

### For more info: [docs](https://docs.cs50.net/2018/x/psets/1/credit/credit.html)
