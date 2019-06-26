import itertools as it
import sys
import time
import crypt


def main():

    if len(sys.argv) != 2:
        print("Usage: python crack.py hash")
        sys.exit(1)

    hash_pwd = sys.argv[1]
    salt = hash_pwd[:2]
    pwd_len = 5
    print("------- crack1 ---------")
    time_brute = 0.0
    before = time.process_time()
    pwd = crack1(hash_pwd, salt, pwd_len)
    after = time.process_time()
    time_brute += after - before
    print(f"TIME crack1: {time_brute:.2f}")
    if pwd:
        print("Password FOUND : ", pwd)
    else:
        print("Password NOT FOUND")
    print("---------- crack2 -----------")
    time_brute = 0.0
    before = time.process_time()
    pwd = crack2(hash_pwd, salt, pwd_len)
    after = time.process_time()
    time_brute += after - before
    print(f"TIME crack1: {time_brute:.2f}")
    if pwd:
        print("Password FOUND : ", pwd)
    else:
        print("Password NOT FOUND")


def crack1(hashd, salt, pwd_len):
    ascii_letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for i in range(1, pwd_len+1):
        for comb in it.product(ascii_letters, repeat=i):
            guess = "".join(comb)
            if crypt.crypt(guess, salt) == hashd:
                return guess
    return None


def crack2(hashd, salt, pwd_len):
    ascii_letters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for fifth in ascii_letters:
        for fourth in ascii_letters:
            for third in ascii_letters:
                for second in ascii_letters:
                    for first in ascii_letters[1:]:
                        guess = f"{first}{second}{third}{fourth}{fifth}".strip()
                        if crypt.crypt(guess, salt) == hashd:
                            return guess
    return None


if __name__ == "__main__":
    main()
