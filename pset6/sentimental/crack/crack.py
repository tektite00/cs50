"""
crack.py is python implementation of crack.c which cracks DES based encryption limited
to passwords no longer than 5 characters long, and not containing numbers or special characters.


"""
import crypt
import sys
import os
import time
import itertools as it


def dict_attack(dict_path, hashd, salt):
    """
    Function performs dictionary attack on provided hashed password in linear time.
    """
    wc = 0
    # Read each word and perform comparison to
    # actual hashed password with crypt output
    with open(dict_path) as f:
        for line in f:
            line = line.rstrip()  # Strips newline character
            wc += 1
            if crypt.crypt(line, salt) == hashd:
                return line, wc
    return None, wc


def brute_force_attack(hashd, salt, pwd_len):
    """
    Function performs brute force attack on provided hashed password,
    which is all possible permutations with repetitons allowed,
    i.e. for 52 letters, and 8 character length password = 52^8 possible
    permutations to check.
    """
    ascii_letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    # Loop through all possible permutations of password
    for i in range(1, pwd_len + 1):
        for comb in it.product(ascii_letters, repeat=i):
            guess = "".join(comb)
            if crypt.crypt(guess, salt) == hashd:
                return guess
    return None


def main():
    # 1. Check argument size
    argc = len(sys.argv)
    if argc != 2 and argc != 3:
        exit("Usage python crack.py [dictionary] hash")

    print("DEBUG| sys.argv => ", sys.argv)
    print("DEBUG| argc => ", argc)

    # 2. Check if dictionary is provided, and file exists
    dict_path = sys.argv[1] if argc == 3 else None
    if dict_path == None or (not os.path.isfile(dict_path)):
        exit(f"Invalid dictionary path: {dict_path}")

    print("DEBUG| dict_path => ", dict_path)

    # 3. Parse hashed password
    hashd = sys.argv[2] if argc == 3 else sys.argv[1]
    print("DEBUG| hash => ", hashd)

    # 4. Extract salt
    salt = hashd[:2]
    # Intialize benchmark vars
    time_dict, time_brute = 0.0, 0.0

    pwd_found = False
    if dict_path:
        print("************************************************")
        print("DICTIONARY ATTACK: Starting [¬º-°]¬ ... [¬º-°]¬ ")
        before = time.process_time()
        passwd, wc = dict_attack(dict_path, hashd, salt)
        after = time.process_time()
        time_dict += after - before  # Update benchmarks
        if passwd:
            print("DICTIONARY ATTACK: Success ...... \\(^-^)/.......")
            print("Password is: ", passwd)
            pwd_found = True
        else:
            print("DICTIONARY ATTACK: Failed ....... (╥﹏╥) .......")
        print(f"WORDS IN DICTIONARY:             {wc}")
        print(f"TIME FOR DICTIONARY ATTACK:      {time_dict:.2f}")
        print("************************************************")

        # If password found, no need to do brute force
        if pwd_found:
            return

    # Max. password length
    pwd_len = 5
    print("************************************************")
    print("BRUTE FORCE ATTACK: Starting ... ᕦ(ò_óˇ)ᕤ .....")
    before = time.process_time()
    passwd = brute_force_attack(hashd, salt, pwd_len)
    after = time.process_time()
    time_brute += after - before  # Update benchmarks
    if passwd:
        print("BRUTE FORCE ATTACK: Sucess .. ┏(-_-)┛┗(-_- )┓..")
        print("Password is: ", passwd)
    else:
        print("BRUTE FORCE ATTACK: Failed ..(╯°□°）╯︵ ┻━┻ ...")
    print(f"TIME FOR BRUTE FORCE ATTACK:     {time_brute:.2f}")
    print("************************************************")


if __name__ == "__main__":
    main()
