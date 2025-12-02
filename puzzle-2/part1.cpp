#include "../cpp-utils/utils.h"

using std::cout;

bool has_repeats(const std::string& value) {
    // need at least 2 digits to repeat
    if (value.size() < 2) return false;
    // odd lengths can't be made up of a 2x repeated substring
    if ((value.size() % 2) != 0) return false;

    return value == repeat(value.substr(0, value.size() / 2), 2);
}

int main() {
    i64 sum = 0;

    auto content = read_file("puzzle-2/input.txt");
    auto ranges = split(content, ',');

    for (const auto& entry: ranges) {
        auto range = split(entry, "-");
        i64 lo = std::stoll(range[0]);
        i64 hi = std::stoll(range[1]);
        for (i64 i = lo; i <= hi; i++) {
            if (has_repeats(std::to_string(i))) {
                sum += i;
            }
        }
    }

    std::cout << "sum: " << sum << "\n";
}
