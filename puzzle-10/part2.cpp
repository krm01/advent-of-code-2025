#include "../cpp-utils/utils.h"
#include <bitset>

using std::cout;

class Machine {
private:
    std::vector<u16> mButtons;
    std::vector<u16> mJoltageSolution;
    std::vector<u16> mCurrentJoltages;

public:
    Machine(const std::string& line) {
        mButtons = Machine::ParseButtons(line);
        mJoltageSolution = Machine::ParseJoltages(line);
        mCurrentJoltages.resize(mJoltageSolution.size());
    }

    void pressButtonJoltage(u16 buttonIdx) {
        u16 button = mButtons.at(buttonIdx);
        u16 i = 0;
        while (i < 16) {
            u16 pressed = (button >> i) & 0x1;
            if (pressed) {
                ++mCurrentJoltages.at(i);
            }
            ++i;
        }
    }

    void reset() {
        mCurrentJoltages.assign(mCurrentJoltages.size(), 0);
    }

    bool isJoltageCountSolved() {
        return mCurrentJoltages == mJoltageSolution;
    }

    i64 numButtons() {
        return mButtons.size();
    }

    void debugPrintState() const {
        cout << ((mCurrentJoltages == mJoltageSolution) ? "✅ SOLVED! \n" : "\n")
             << "buttons : ";

        for (const auto& button : mButtons) {
            cout << "(" << std::bitset<16>(button) << ") ";
        }

        cout << "\njoltages: ";

        for (i64 i = 0; i < mJoltageSolution.size(); ++i) {
            cout << "{" << mCurrentJoltages.at(i) << "," << mJoltageSolution.at(i) << "} ";
        }
        cout << "\n------------------\n";
    }

private:
    static std::vector<u16> ParseButtons(const std::string& input) {
        std::vector<u16> buttons;

        for (i64 i = input.find_first_of('(') + 1; i < input.find_first_of('{') - 1;) {
            i64 length = input.find_first_of(')', i) - i;
            u16 button = 0;
            for (const auto& value : split(input.substr(i, length), ',')) {
                button |= 1 << std::stoll(value);
            }

            buttons.emplace_back(button);
            i += length + 3;
        }

        return buttons;
    }

    static std::vector<u16> ParseJoltages(const std::string& input) {
        std::vector<u16> joltages;

        i64 begin = input.find_first_of('{') + 1;
        const auto view = input.substr(begin, input.find_first_of('}') - begin);
        for (const auto& value : split(view, ',')) {
            joltages.emplace_back(std::stoll(value));
        }

        return joltages;
    }
};

// try to solve by iterating all the (n multichoose k) elements: C(n+k-1, k)
i64 brute_force_solve(Machine& machine) {
    i64 n = machine.numButtons();

    // if it takes a million button presses it's fucked anyway
    for (i64 k = 1; k < 1'000'000; ++k) {
        std::vector<i64> pattern(k, 0);
        while (true) {
            machine.reset();
            for (i64 i = 0; i < pattern.size(); ++i) {
                machine.pressButtonJoltage(pattern[i]);
            }

            if (machine.isJoltageCountSolved()) {
                return k;
            }


            // generate the next pattern for k presses
            i64 i = k - 1;
            while (i >= 0 && pattern[i] == n - 1) {
                --i;
            }
            if (i < 0) break;

            ++pattern[i];
            
            for (i64 j = i + 1; j < k; j++) {
                pattern[j] = pattern[i];
            }
        }
    }

    throw "the alg is broken man";
}


i64 solve_machines(std::vector<Machine>& machines) {
    i64 sumOfMinPresses = 0;

    i64 i = 0;
    for (auto& machine : machines) {
        sumOfMinPresses += brute_force_solve(machine);
        cout << "[" << i << "] ";
        machine.debugPrintState();
    }

    return sumOfMinPresses;
}

int main() {
    auto content = read_file("puzzle-10/test-input.txt");
    // auto content = read_file("puzzle-10/input.txt");

    cout << "This solution technically could work for the real puzzle "
        << "input, but i might die before it finishes. solving this "
        << "quickly requires more math than i'm willing to implement.";

    return 0;

    std::vector<Machine> machines;
    for (const auto& line : split(content, '\n')) {
        machines.emplace_back(line);
    }

    i64 solution = solve_machines(machines);

    cout << "solution: " << solution << "\n";
}
