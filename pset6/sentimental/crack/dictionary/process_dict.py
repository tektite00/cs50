def isascii(s):
    return len(s) == len(s.encode())

PASSWORD_LENGTH = 5

words = []
count = 0
with open('dict.txt', 'r') as fr:
    with open('words.txt', 'w') as fw:
        for line in fr:
            line = line.rstrip()
            if isascii(line):
                if line.endswith("'s"):
                    line = line[:-2]
                if len(line) > PASSWORD_LENGTH:
                    continue
                if line not in words:
                    words.append(line)
                    count += 1

print(f"Words processed with length <= 5 and ASCII chars: {count}")

count = 0
with open('words.txt', 'w') as fw:
    for word in words:
        fw.write(word + '\n')
        count += 1

print(f"Words wrote to 'words.txt' file: {count}")
