#include "../cpp-utils/utils.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using std::cout;

struct Point {
    i64 x, y;
};

u64 calc_area(const Point& a, const Point& b) {
    i64 dx = std::abs(b.x - a.x) + 1;
    i64 dy = std::abs(b.y - a.y) + 1;
    return dx * dy;
}

int main() {
    // auto content = read_file("puzzle-9/test-input.txt");
    auto content = read_file("puzzle-9/input.txt");

    std::vector<Point> points;
    auto lines = split(content, '\n');
    points.reserve(lines.size());
    for (const auto& line : lines) {
        auto coords = split(line, ',');
        points.emplace_back(std::stoll(coords.at(0)), std::stoll(coords.at(1)));
    }

    i64 maxArea = 0;
    for (i64 i = 0; i < lines.size(); ++i) {
        for (i64 k = i+1; k < lines.size(); ++k) {
            i64 area = calc_area(points[i], points[k]);
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    cout << "solution: " << maxArea << "\n";
}
