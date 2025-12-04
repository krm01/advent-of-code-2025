#include "../cpp-utils/utils.h"
#include <algorithm>
#include <array>

using std::cout;

i64 accessible_roll_count(const std::string& content) {
    const i64 m = content.find('\n');
    const i64 n = std::count(content.begin(), content.end(), '\n') + 1;
    static constexpr std::array<std::pair<i64, i64>, 8> checks = {{
        { -1,  1 }, {  0,  1 }, {  1,  1 },
        { -1,  0 },             {  1,  0 },
        { -1, -1 }, {  0, -1 }, {  1, -1 }
    }};

    i64 n_accessible = 0;

    for (i64 y = 0; y < m; y++) {
        for (i64 x = 0; x < n; x++) {
            if (content[y * m + x + y] != '@') {
                continue;
            }

            i64 n_adjacent = 0;
            for (const auto& [y_, x_]: checks) {
                i64 x2 = x + x_;
                i64 y2 = y + y_;

                if (x2 < 0 || x2 >= n) continue;
                if (y2 < 0 || y2 >= m) continue;

                if (content[y2 * m + x2 + y2] == '@') {
                    n_adjacent++;
                }

                if (n_adjacent >= 4) {
                    break;
                }
            }

            if (n_adjacent < 4) {
                n_accessible++;
            }
        }
    }

    return n_accessible;
}


void test() {
    auto content = read_file("puzzle-4/test-input.txt");
    auto solution = "..xx.xx@x." "\n"
                    "x@@.@.@.@@" "\n"
                    "@@@@@.x.@@" "\n"
                    "@.@@@@..@." "\n"
                    "x@.@@@@.@x" "\n"
                    ".@@@@@@@.@" "\n"
                    ".@.@.@.@@@" "\n"
                    "x.@@@.@@@@" "\n"
                    ".@@@@@@@@." "\n"
                    "x.x.@@@.x.";

    i64 total = accessible_roll_count(content);
    cout << "\n==============\n" << content
    << "\n--------------\n" << solution << "\n\n";
    cout << "total: " << total << "\n";
}

int main() {
    // test(); return 0;
    auto content = read_file("puzzle-4/input.txt");
    i64 total = accessible_roll_count(content);
    cout << "total: " << total << "\n";
}
