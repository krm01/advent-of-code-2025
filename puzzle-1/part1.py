#!/bin/bash
def main(dial=50, dial_mod=99+1, path="input.txt"):
    zero_count = 0
    with open(path) as fd:
        for line in fd:
            amt = int(line[1:])
            dial = (dial - amt if line[0] == "L" else dial + amt) % dial_mod
            zero_count += dial == 0

    print(zero_count)


if __name__ == "__main__":
    main()

