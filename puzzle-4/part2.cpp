#include "../cpp-utils/utils.h"
#include <algorithm>
#include <array>

using std::cout;

i64 accessible_roll_count(std::string& content) {
    const i64 m = content.find('\n');
    const i64 n = std::count(content.begin(), content.end(), '\n') + 1;
    static constexpr std::array<std::pair<i64, i64>, 8> checks = {{
        { -1,  1 }, {  0,  1 }, {  1,  1 },
        { -1,  0 },             {  1,  0 },
        { -1, -1 }, {  0, -1 }, {  1, -1 }
    }};

    i64 n_removed_total = 0;
    i64 n_removed = 0;
    do {
        n_removed = 0;

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
                    content[y * m + x + y] = '.';
                    n_removed++;
                }
            }
        }

        n_removed_total += n_removed;
    } while (n_removed > 0);

    return n_removed_total;
}


void test() {
    auto content = read_file("puzzle-4/test-input.txt");
    auto orig_content = content;

    i64 total = accessible_roll_count(content);
    cout << "\n==============\n" << orig_content
    << "\n--------------\n" << content << "\n\n";
    cout << "total: " << total << "\n";
}

int main() {
    // test(); return 0;
    auto content = read_file("puzzle-4/input.txt");
    i64 total = accessible_roll_count(content);
    cout << "removed: " << total << "\n";
}
