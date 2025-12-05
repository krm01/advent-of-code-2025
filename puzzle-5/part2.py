def merge_ranges(ranges):
    ranges.sort(key=lambda it: it[0])
    merged = []

    for lo, hi in ranges:
        if not merged or lo > merged[-1][1]:
            merged.append([lo, hi])
        else:
            merged[-1][1] = max(merged[-1][1], hi)

    return merged

def main(path):
    ranges = []
    with open(path) as fd:
        for line in fd:
            if "-" in line:
                ranges.append([int(it) for it in line.split("-")])
            else:
                break
    
    merged = merge_ranges(ranges)

    total = 0
    for lo, hi in merged:
        total += hi - lo
        total += 1
    
    print(f"{total=}")

if __name__ == "__main__":
    main("puzzle-5/input.txt")