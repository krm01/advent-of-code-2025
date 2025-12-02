#include "../cpp-utils/utils.h"

using std::cout;

// incorrect logic. this finds repeats of any length, but the question
// wanted a sequence of digits repeated TWICE.
bool has_repeats_wrong(const std::string& value) {
    // need at least 2 digits to repeat
    if (value.size() < 2) return false;

    // only need to check single-char repeat for prime lengths
    if (is_prime(value.size())) {
        return value == repeat(value[0], value.size());
    }

    for (i64 cycle_len = 1; cycle_len <= value.size() / 2; cycle_len++) {
        auto [n_cycles, rem] = divrem(value.size(), cycle_len);

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

bool has_repeats(const std::string& value) {
    // need at least 2 digits to repeat
    if (value.size() < 2) return false;
    // odd lengths can't be made up of a 2x repeated substring
    if ((value.size() % 2) != 0) return false;

    return value == repeat(value.substr(0, value.size() / 2), 2);
}

void test_range() {
    i32 lo = 95;
    i32 hi = 115;
    i32 invalid = 99;


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
    /* ATTEMPTS */
    // 20077272987 TOO HIGH
}
