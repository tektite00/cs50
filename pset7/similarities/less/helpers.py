from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    lines_a = set(a.split("\n"))
    lines_b = set(b.split("\n"))
    return list(lines_a.intersection(lines_b))


def sentences(a, b):
    """Return sentences in both a and b"""
    sents_a = set(sent_tokenize(a))
    sents_b = set(sent_tokenize(b))
    return list(sents_a.intersection(sents_b))


def substr_tokenize(string, n):
    """Tokenizes string into substrings of n size/length"""
    return [string[i:n+i] for i in range(len(string) - n + 1)]


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings_a = set(substr_tokenize(a, n))
    substrings_b = set(substr_tokenize(b, n))
    return list(substrings_a.intersection(substrings_b))
