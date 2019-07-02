from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    # Get length of strings
    n_a = len(a) + 1
    n_b = len(b) + 1

    # Initialize the cost matrix - Set's up 2D list
    cost = [[(0, None) for _ in range(n_b)] for _ in range(n_a)]

    # Add values for base cases - first row and first column
    for i in range(n_a):
        for j in range(n_b):
            if i == 0 and j == 0:
                continue
            elif i == 0 and j != 0:
                cost[i][j] = (j, Operation.INSERTED)
            elif j == 0 and i != 0:
                cost[i][j] = (i, Operation.DELETED)
            else:
                # An Array to hold edit distances
                edit_distances = [
                    (cost[i-1][j][0] + 1, Operation.DELETED),
                    (cost[i][j-1][0] + 1, Operation.INSERTED),
                    (cost[i-1][j-1][0] + 1 if a[i-1] != b[j-1] else cost[i-1][j-1][0], Operation.SUBSTITUTED)
                ]
                cost[i][j]= min(edit_distances, key = lambda t: t[0])
                print(f"min(cost[{i}][{j}]): ",
                        edit_distances, " min = ", cost[i][j])
    return cost


# cost=distances("CAT", "ATE")
# for row in cost:
#     for col in row:
#         print(col, end="\t")
#     print()
