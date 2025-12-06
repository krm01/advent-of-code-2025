#include "../cpp-utils/utils.h"

using std::cout;


int main() {
    // auto content = read_file("puzzle-6/test-input.txt");
    const auto content = read_file("puzzle-6/input2.txt");

    std::vector<std::vector<i64>> numbers;
    std::vector<std::string> operators;

    for (const auto& line : split(content, '\n')) {
        const auto tokens = split(line, ' ');

        if (tokens[0] == "+" || tokens[0] == "*") {
            operators = std::move(tokens);
        } else {
            numbers.emplace_back();
            auto& tail = numbers.back();
            for (const auto& token : tokens) {
                tail.emplace_back(std::stoll(token));
            }
        }
    }

    i64 total = 0;
    for (i64 i = 0; i < operators.size(); ++i) {
        i64 result = (operators[i] == "+") ? 0 : 1;
        for (i64 k = 0; k < numbers.size(); ++k) {
            if (operators[i] == "+") {
                result += numbers[k][i];
            } else {
                result *= numbers[k][i];
            }
        }
        total += result;
    }

    cout << "total: " << total << "\n";
}
