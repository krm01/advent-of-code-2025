#include "../cpp-utils/utils.h"

using std::cout;

bool has_repeats(const std::string& value) {
    // need at least 2 digits to repeat
    if (value.size() < 2) return false;

    // only need to check single-char repeat for prime lengths
    if (is_prime(value.size())) {
        return value == repeat(value[0], value.size());
    }

    for (i64 cycle_len = 1; cycle_len <= value.size() / 2; cycle_len++) {
        auto [n_cycles, rem] = std::div(value.size(), cycle_len);

        // skip any cycles that can't fully repeat
        if (rem != 0) {
            continue;
        }

        if (value == repeat(value.substr(0, cycle_len), n_cycles)) {
            return true;
        }
    }

    return false;
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

    cout << "sum: " << sum << "\n";

}
