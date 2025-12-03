#include "../cpp-utils/utils.h"

using std::cout;

i64 find_max_joltage(const std::string& bank) {
    i64 pos = bank.size() - 1;
    i64 ones = pos;
    i64 tens = pos - 1;

    for (pos = tens - 1; pos >= 0; pos--) {
        if (bank[pos] >= bank[tens]) {
            if (bank[tens] >= bank[ones]) {
                ones = tens;
            }
            tens = pos;
        }
    }

    return ((bank[tens] - '0') * 10) + (bank[ones] - '0');
}

void test() {
    auto content = read_file("puzzle-3/test-input.txt");

    i64 expected_joltages[] = { 98, 89, 78, 92 };
    i64 expected_sum = 357;

    auto banks = split(content, '\n');

    i64 actual_sum = 0;
    for (size_t i = 0; i < std::size(expected_joltages); i++) {
        i64 joltage = find_max_joltage(banks[i]);
        actual_sum += joltage;
        cout << RESULT_MARK[expected_joltages[i] == joltage]
            << " expected: " << expected_joltages[i]
            << " actual: " << joltage << "\n";
    }

    cout << "------------\n" << RESULT_MARK[expected_sum == actual_sum]
        << " expected sum: " << expected_sum 
        << " actual_sum: " << actual_sum << "\n";
}

int main() {
    // test(); return 0;
    auto content = read_file("puzzle-3/input.txt");
    
    i64 sum = 0;
    for (const auto& bank : split(content, '\n')) {
        sum += find_max_joltage(bank);
    }

    cout << sum << "\n";
}
