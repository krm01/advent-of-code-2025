#!/bin/bash
def main(dial=50, dial_mod=99+1, path="input.txt"):
    zero_count = 0
    with open(path) as fd:
        for line in fd:
            amt = int(line[1:])

            start_pos = dial
            q, dial = divmod(dial - amt if line[0] == "L" else dial + amt, dial_mod)
            zero_count += abs(q)
            
            # fix annoying fucking rotate left behavior
            if line[0] == "L":
                if start_pos == 0 and dial != 0:
                    zero_count -= 1  # started at 0
                elif start_pos != 0 and dial == 0:
                    zero_count += 1  # landed on 0
            
    print(zero_count)

if __name__ == "__main__":
    main()

