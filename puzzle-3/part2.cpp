#include "../cpp-utils/utils.h"
#include <cmath>

using std::cout;

i64 find_max_joltage(const std::string& bank, i64 n_batteries) {
    i64 pos = bank.size() - 1;
    std::vector<i64> enabled(n_batteries);

    // preload the enabled batteries as the last n in the bank
    for (i64 i = n_batteries - 1; i >= 0; i--, pos--) {
        enabled[i] = pos;
    }

    // pos already set from previous loop
    for (; pos >= 0; pos--) {
        if (bank[pos] >= bank[enabled[0]]) {
            i64 prev_idx = enabled[0];
            enabled[0] = pos;

            for (i64 i = 1; i < n_batteries; i++) {
                if (bank[prev_idx] >= bank[enabled[i]]) {
                    // move enable[i] to prev_idx and update prev_idx, aka swap
                    std::swap(enabled[i], prev_idx);
                } else {
                    // enforce ordinality of enabled batteries.
                    // stop shifting after 1st lower value, no "jumping over"
                    break;
                }
            }
        }
    }

    // accumulate into integer, each *10 shifts the "place" left per iteration
    i64 joltage = 0;
    for (i64 i = 0; i < n_batteries; i++) {
        joltage = (joltage * 10) + bank[enabled[i]] - '0'; 
    }

    return joltage;
}

int main() {
    auto content = read_file("puzzle-3/input.txt");
    
    i64 sum = 0;
    for (const auto& bank : split(content, '\n')) {
        sum += find_max_joltage(bank, 12);
    }

    cout << sum << "\n";
}
