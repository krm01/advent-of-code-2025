#include "../cpp-utils/utils.h"

#include <unordered_set>

using std::cout;

i64 count_beam_splits(const std::vector<std::string>& lines) {
    i64 nSplits = 0;
    std::unordered_set<i64> beams;

    for (const auto& line : lines) {
        if (beams.size() == 0) {
            beams.insert(lines[0].find('S'));
            continue;
        }

        for (i64 i = 0; i < line.size(); ++i) {
            if ((line[i] == '^') && beams.contains(i)) {
                beams.erase(i);
                beams.insert(i-1);
                beams.insert(i+1);
                ++nSplits;
            }
        }
    }

    return nSplits;
}

int main() {
    // auto content = read_file("puzzle-7/test-input.txt");
    auto content = read_file("puzzle-7/input.txt");

    auto lines = split(content, '\n');
    i64 nSplits = count_beam_splits(lines);


    cout << "splits: " << nSplits << "\n";
}
