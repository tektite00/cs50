"""
hello.py prints out a simple greeting to the user, per the below.

USAGE:
```
$ python hello.py
What is your name?
David
hello, David
```
"""
# Ask for name
name = input("What is your name?\n")
# Print name
print(f"hello, {name}")
