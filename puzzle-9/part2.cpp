#include "../cpp-utils/utils.h"
#include <unordered_set>
#include <unordered_map>

using std::cout;
using EdgeList = std::unordered_map<i64, std::vector<struct Point>>;

struct Point {
    i64 x, y;
};

u64 calc_area(const Point& a, const Point& b) {
    i64 dx = std::abs(b.x - a.x) + 1;
    i64 dy = std::abs(b.y - a.y) + 1;
    return dx * dy;
}

bool is_rect_inside(const EdgeList& xEdgeList, const EdgeList& yEdgeList, const Point& p1, const Point& p2) {
    // the rectangle is formed by any 2 arbitrary points. so
    // first "normalize" them so we're always using the
    // top left and bottom right points.
    Point topLeft(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
    Point topRight(std::max(p1.x, p2.x), std::max(p1.y, p2.y));

 
    // "racast" between the points that form the subrectangle
    // by checking the edgeList for intersections. if no edges
    // the rectangle MUST be fully inside the greater polygon
    for (const auto& [x, edges] : xEdgeList) {
        if (x <= topLeft.x || x >= topRight.x) continue;
        for (const auto& [yMin, yMax] : edges) {
            if (yMin < topRight.y && yMax > topLeft.y) return false;
        }
    }
    
    for (const auto& [y, edges] : yEdgeList) {
        if (y <= topLeft.y || y >= topRight.y) continue;
        for (const auto& [xMin, xMax] : edges) {
            if (xMin < topRight.x && xMax > topLeft.x) return false;
        }
    }
    
    return true;
}

void update_edges(EdgeList& xEdgeList, EdgeList& yEdgeList, i64 xPrev, i64 x, i64 yPrev, i64 y) {
    if ((x == xPrev) && (y != yPrev)) {
        xEdgeList[x].emplace_back(std::min(y, yPrev), std::max(y, yPrev));
    } else if ((y == yPrev) && (x != xPrev)) {
        yEdgeList[y].emplace_back(std::min(x, xPrev), std::max(x, xPrev));
    }
}

int main() {
    // auto content = read_file("puzzle-9/input.txt");
    auto content = read_file("puzzle-9/input.txt");

    std::vector<Point> points;
    EdgeList xEdgeList;
    EdgeList yEdgeList;
    auto lines = split(content, '\n');
    points.reserve(lines.size());

    i64 xPrev = -1;
    i64 yPrev = -1;
    for (const auto& line : lines) {
        const auto& coords = split(line, ',');
        i64 x = std::stoll(coords.at(0));
        i64 y = std::stoll(coords.at(1));

        if (xPrev > -1) {
            update_edges(xEdgeList, yEdgeList, xPrev, x, yPrev, y);
        }

        xPrev = x;
        yPrev = y;
        points.emplace_back(x, y);
    }

    // wrap the last one back to the first to form the final edge
    {
        const auto& firstPoint = split(lines[0], ',');
        i64 x = std::stoll(firstPoint[0]);
        i64 y = std::stoll(firstPoint[1]);
        update_edges(xEdgeList, yEdgeList, xPrev, x, yPrev, y);
    }


    i64 maxArea = 0;
    for (i64 i = 0; i < points.size(); ++i) {
        for (i64 k = i+1; k < points.size(); ++k) {
            Point& p1 = points[i];
            Point& p2 = points[k];
            i64 area = calc_area(p1, p2);
            if (area > maxArea && is_rect_inside(xEdgeList, yEdgeList, p1, p2)) {
                maxArea = area;
            }
        }
    }

    cout << "maxArea: " << maxArea << "\n";
}
