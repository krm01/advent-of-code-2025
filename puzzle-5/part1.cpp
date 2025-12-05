#include "../cpp-utils/utils.h"
#include <span>
#include <cassert>

using std::cout;

std::vector<std::pair<i64, i64>> combine_ranges(const std::span<std::string>& raw_ranges) {
    std::vector<std::pair<i64, i64>> ranges;
    ranges.reserve(raw_ranges.size());

    for (const auto& raw_range : raw_ranges) {
        auto range = split(raw_range, '-');
        ranges.emplace_back(std::stoll(range[0]), std::stoll(range[1]));
    }

    return ranges;
}

bool id_in_ranges(const std::vector<std::pair<i64, i64>>& ranges, i64 id) {
    for (const auto& [lo, hi] : ranges) {
        if (lo <= id  && id <= hi) {
            return true;
        }
    }

    return false;
}

int main() {
    // auto content = read_file("puzzle-5/test-input.txt");
    auto content = read_file("puzzle-5/input.txt");

    auto lines = split(content, '\n');

    i64 split_idx = 0;
    for (split_idx = 0; split_idx < lines.size(); split_idx++) {
        if (lines[split_idx].empty()) {
            break;
        }
    }

    std::span<std::string> raw_ranges(lines.begin(), lines.begin() + split_idx);
    std::span<std::string> ids(lines.begin() + split_idx + 1, lines.end());

    i64 n_fresh = 0;
    auto ranges = combine_ranges(raw_ranges);
    for (const auto& id : ids) {
        assert(id != "");
        if (id_in_ranges(ranges, std::stoll(id))) {
            n_fresh++;
        }
    }

    cout << "n_fresh=" << n_fresh << "\n";
}
