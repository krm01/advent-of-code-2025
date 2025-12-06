import operator
from collections import defaultdict

def main():
    with open("puzzle-6/input.txt") as fd:
        lines = fd.read().split("\n")

    lines = lines[:-1]

    numbers = defaultdict(list)
    ops = []

    # load strings into lists
    i = 0
    while i < len(lines[-1]):
        width = 1

        while i+width < len(lines[-1]) and lines[-1][i+width] == ' ':
            width += 1
 
        for line in lines[:-1]:
            numbers[len(ops)].append(line[i:i+width])
        
        ops.append(operator.add if lines[-1][i] == "+" else operator.mul)
        i += width
 
    # convert to weird numbers and sum
    total = 0
    for idx, op in enumerate(ops):
        cur_value = 0 if op == operator.add else 1
        width = len(numbers[idx][0]) - 1

        while width >= 0:
            number = ""
            for it in numbers[idx]:
                if it[width] != " ":
                    number += it[width]
 
            if number != "":
                cur_value = op(cur_value, int(number))
            width -= 1
        
        total += cur_value

    print(f"{total=}")


if __name__ == "__main__":
    main()
