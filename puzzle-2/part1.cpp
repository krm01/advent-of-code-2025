#include "../cpp-utils/utils.h"


bool has_repeats(const std::string& value) {
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

void test_range() {
    i32 lo = 95;
    i32 hi = 115;
    i32 invalid = 99;


}

int main() {
    auto content = read_file("input.txt");

    std::string invalids[] = { "987123", "34981251", "875", "98732", "61792347" };


    std::string valids[] = { "99", "11", "22", "1010", "222222", "446446", "38593859" };
    for (const auto& value : valids) {
        std::cout << RESULT_MARK[has_repeats(value)] << "  " << value << "\n";
    }

    std::cout << "Testing invalid: =====\n";
    for (const auto& value : invalids) {
        std::cout << RESULT_MARK[has_repeats(value)] << "  " << value << "\n";
    }

}
