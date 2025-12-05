#include "../cpp-utils/utils.h"
#include <span>
#include <cassert>
#include <algorithm>
#include <cstdio>

using std::cout;

std::vector<std::pair<i64, i64>> combine_ranges(const std::span<const std::string>& raw_ranges) {
    std::vector<std::pair<i64, i64>> ranges;
    ranges.reserve(raw_ranges.size());
    std::vector<std::pair<i64, i64>> combined_ranges;
    combined_ranges.reserve(raw_ranges.size());

    for (const auto& raw_range : raw_ranges) {
        const auto range = split(raw_range, '-');
        ranges.emplace_back(std::stoll(range[0]), std::stoll(range[1]));
    }

    std::sort(ranges.begin(), ranges.end());

    for (const auto& [lo, hi] : ranges) {
        if (combined_ranges.empty() || lo > combined_ranges.back().second) {
            combined_ranges.emplace_back(lo, hi);
        } else {
            combined_ranges.back().second = std::max(combined_ranges.back().second, hi);
        }
    }

    return combined_ranges;
}

int main() {
    // auto content = read_file("puzzle-5/test-input.txt");
    const auto content = read_file("puzzle-5/input.txt");

    const auto lines = split(content, '\n');

    // only care about first part of file that has ranges, discard after empty line
    i64 split_idx = 0;
    for (split_idx = 0; split_idx < lines.size(); split_idx++) {
        if (lines[split_idx].empty()) {
            break;
        }
    }

    const std::span<const std::string> raw_ranges(lines.cbegin(), lines.cbegin() + split_idx);

    i64 n_ids = 0;
    for (const auto& [lo, hi] : combine_ranges(raw_ranges)) {
        n_ids += hi - lo + 1;
    }

    cout << "n_ids=" << n_ids << "\n\n";
}
