#include "../cpp-utils/utils.h"
#include <unordered_map>

using std::cout;

struct DagNode {
    std::pair<i64, i64> id, left, right;
};

std::pair<i64, i64> cast_beam(const std::vector<std::string>& lines, i64 row, i64 col) {
    while (row < lines.size() && col <= lines[row].size()) {
        if (lines[row][col] == '^') {
            return { row, col };
        }
        ++row;
    }

    return { -1, col };
}

std::vector<DagNode> construct_dag(const std::vector<std::string>& lines) {
    std::vector<DagNode> dag;

    for (i64 r = 2; r < lines.size(); r+=2) {
        for (i64 i = 0; i < lines[r].size(); ++i) {
            if (lines[r][i] == '^') {
                dag.emplace_back(
                    std::pair<i64, i64> {r, i},
                    cast_beam(lines, r+1, i-1),
                    cast_beam(lines, r+1, i+1)
                );
            }
        }
    }

    return dag;
}

// assumes the DAG is already sorted (which it will be from the construction logic)
i64 count_paths(const std::vector<DagNode>& dag, i64 lineWidth) {
    // pair<int, int> isn't hashable as a key so gotta do it manually
    auto key = [lineWidth](std::pair<i64, i64> k) {
        return lineWidth * k.first + k.second;
    };

    i64 totalPaths = 0;
    std::unordered_map<i64, i64> pathCounts;
    pathCounts[key(dag[0].id)] = 1;

    for (const auto& node : dag) {
        i64 nPaths = pathCounts[key(node.id)];
        pathCounts[key(node.left)] += nPaths;
        pathCounts[key(node.right)] += nPaths;
        if (node.left.first == -1) totalPaths += nPaths;
        if (node.right.first == -1) totalPaths += nPaths;
    }

    return totalPaths;
}

int main() {
    // auto content = read_file("puzzle-7/test-input.txt");
    auto content = read_file("puzzle-7/input.txt");

    auto lines = split(content, '\n');
    auto dag = construct_dag(lines);
    i64 nTimelines = count_paths(dag, lines[0].size());

    cout << "timelines: " << nTimelines << "\n";
}
