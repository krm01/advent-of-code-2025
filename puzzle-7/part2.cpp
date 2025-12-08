#include "../cpp-utils/utils.h"

#include <unordered_map>

using std::cout;

typedef struct DagNode {
    std::pair<i64, i64> id;
    std::pair<i64, i64> left;
    std::pair<i64, i64> right;
} DagNode;

std::pair<i64, i64> cast_beam(const std::vector<std::string>& lines, i64 row, i64 col) {
    while (row < lines.size()) {
        if (lines[row][col] == '^') {
            return { row, col };
        }
        ++row;
    }

    return { -1, col };
}

i64 count_beam_timelines(const std::vector<std::string>& lines) {
    std::vector<DagNode> dag;

    for (i64 r = 0; r < lines.size(); ++r) {
        const auto& line = lines[r];

        for (i64 i = 0; i < line.size(); ++i) {
            if (line[i] == '^') {
                dag.emplace_back(
                    std::pair<i64, i64> {r, i},
                    cast_beam(lines, r+1, i-1),
                    cast_beam(lines, r+1, i+1)
                );
            }
        }
    }

    // for (const auto& node : dag) {
    //     cout << "node: (" << node.id.first << "," << node.id.second << ")"
    //         << "   L: (" << node.left.first  << ", " << node.left.second << ")"
    //         << "   R: (" << node.right.first  << ", " << node.right.second << ")"
    //         << "\n";
    // }

    std::unordered_map<i64, i64> nPaths;
    i64 offset = lines[0].size();
    auto key = [offset](std::pair<i64, i64> k) {
        return offset * k.first + k.second;
    };

    // initialize root to 1 for incoming beam from S
    nPaths[key(dag[0].id)] = 1;
    for (const auto& node : dag) {
        nPaths[key(node.left)] += nPaths[key(node.id)];
        nPaths[key(node.right)] += nPaths[key(node.id)];
    }

    // sum paths of all unique leaves (row == -1)
    i64 totalPaths = 0;
    for (const auto& [k, v]: nPaths) {
        if (k < 0) {
            totalPaths += v;
        }
    }

    return totalPaths;
}

int main() {
    // auto content = read_file("puzzle-7/test-input.txt");
    auto content = read_file("puzzle-7/input.txt");

    auto lines = split(content, '\n');
    i64 nTimelines = count_beam_timelines(lines);


    cout << "timelines: " << nTimelines << "\n";
}
