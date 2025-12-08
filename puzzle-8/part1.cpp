#include "../cpp-utils/utils.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using std::cout;

struct Point {
    std::string id;
    i64 x, y, z;
};

struct DistanceEntry {
    std::string a;
    std::string b;
    u64 distsq;
};

struct Comparator {
    bool operator()(const DistanceEntry& a, DistanceEntry& b) const {
        return a.distsq < b.distsq; // maxheap (top element is largest)
    }
};

u64 distsq_xyz(const Point& a, const Point& b) {
    i64 dx = b.x - a.x;
    i64 dy = b.y - a.y;
    i64 dz = b.z - a.z;
    return dx*dx + dy*dy + dz*dz;
}

class UnionFind {
private:
    std::unordered_map<std::string, std::string> parent;

public:
    void add(const std::string& x) {
        parent[x] = x;
    }

    std::string find(const std::string& x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(const std::string& a, const std::string& b) {
        parent[find(a)] = find(b);
    }
};


std::vector<std::unordered_set<std::string>>
create_circuits(const std::vector<std::string>& strPoints, i64 nConnections) {
    std::vector<Point> points;
    points.reserve(strPoints.size());
    std::priority_queue<DistanceEntry, std::vector<DistanceEntry>, Comparator> distHeap;
    UnionFind uf;

    // make Points
    for (const auto& line : strPoints) {
        auto vals = split(line, ',');
        points.emplace_back(line, std::stoll(vals[0]), std::stoll(vals[1]), std::stoll(vals[2]));
        uf.add(line);
    }

    // store distances in the minheap
    for (i64 i = 0; i < points.size(); ++i) {
        for (i64 k = i+1; k < points.size(); ++k) {
            u64 distsq = distsq_xyz(points[i], points[k]);

            if (distHeap.size() < nConnections) {
                distHeap.emplace(points[i].id, points[k].id, distsq);
            } else if (distsq < distHeap.top().distsq) {
                distHeap.pop();
                distHeap.emplace(points[i].id, points[k].id, distsq);
            }
        }
    }

    // connect all the closest points
    while (distHeap.size() > 0) {
        const auto& entry = distHeap.top();
        uf.unite(entry.a, entry.b);
        distHeap.pop();
    }

    // merge 'em. basically combine overlapping sets (the whole point of UnionFind)
    std::unordered_map<std::string, std::unordered_set<std::string>> circuitsByRoot;
    for (const auto& point : points) {
        circuitsByRoot[uf.find(point.id)].insert(point.id);
    }

    // need to move to a vector so we can sort them by size and return
    std::vector<std::unordered_set<std::string>> circuits;
    for (auto& [_, circuit] : circuitsByRoot) {
        circuits.push_back(std::move(circuit));
    }
    
    std::sort(circuits.begin(), circuits.end(), [](const auto& a, const auto& b){
        return a.size() > b.size();
    });

    return circuits;
}


int main() {
    // auto content = read_file("puzzle-8/test-input.txt");
    auto content = read_file("puzzle-8/input.txt");

    auto lines = split(content, '\n');

    std::vector<std::unordered_set<std::string>> circuits = create_circuits(lines, 1000);

    i64 nLargest = 3;
    i64 solution = 1;
    for (i64 i = 0; i < nLargest; ++i) {
        solution *= circuits[i].size();
    }

    cout << "solution: " << solution << "\n";
}
