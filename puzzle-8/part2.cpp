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
        return a.distsq > b.distsq; // minheap this time (top is smallest)
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
    i64 nCircuits;
    UnionFind() : nCircuits(0) {} // tf is this ugly ass syntax bro on god fr no cap fr rn

    void add(const std::string& x) {
        parent[x] = x;
        ++nCircuits;
    }

    std::string find(const std::string& x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(const std::string& a, const std::string& b) {
        auto aRoot = find(a);
        auto bRoot = find(b);

        // now need to check roots being different, aka a true "merge"
        if (aRoot != bRoot) {
            parent[aRoot] = bRoot;
            --nCircuits;
        }
    }
};


// now returns distance to wall after all points are fully connected in 1 circuit
i64 create_circuits(const std::vector<std::string>& strPoints) {
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

            // now store every distance instead of only shortest 1000
            // since we dont know how many connections will be needed
            distHeap.emplace(points[i].id, points[k].id, distsq);
        }
    }

    // connect all the closest points
    while (distHeap.size() > 0) {
        const auto& entry = distHeap.top();
        uf.unite(entry.a, entry.b);

        // check if the last connection just completed into 1 circuit
        if (uf.nCircuits == 1) {
            auto ax = std::stoll(split(entry.a, ',')[0]);
            auto bx = std::stoll(split(entry.b, ',')[0]);
            return ax * bx;
        }
 
        distHeap.pop();
    }
    return -1;
}


int main() {
    // auto content = read_file("puzzle-8/test-input.txt");
    auto content = read_file("puzzle-8/input.txt");
    auto lines = split(content, '\n');
    i64 wallDist = create_circuits(lines);
    cout << "solution: " << wallDist << "\n";
}
