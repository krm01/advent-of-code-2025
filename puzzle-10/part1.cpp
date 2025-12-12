#include "../cpp-utils/utils.h"
#include <bitset>

using std::cout;

class Machine {
private:
    u64 mPressedCount;
    u16 mSolutionPattern;
    u16 mCurrentPattern;
    std::vector<u16> mButtons;

public:
    Machine(const std::string& line) {
        mPressedCount = 0;
        mCurrentPattern = 0;
        mSolutionPattern = Machine::ParseLights(line);
        mButtons = Machine::ParseButtons(line);
    }

    bool pressButton(size_t buttonIdx) {
        mCurrentPattern ^= mButtons.at(buttonIdx);
        ++mPressedCount;
        return mCurrentPattern == mSolutionPattern;
    }

    void reset() {
        mCurrentPattern = 0;
        mPressedCount = 0;
    }

    bool isSolved() {
        return mCurrentPattern == mSolutionPattern;
    }

    i64 numButtons() {
        return mButtons.size();
    }

    void debugPrintState() const {
        cout << ((mSolutionPattern == mCurrentPattern) ? "✅ SOLVED! \n" : "\n")
             << "solution: " << std::bitset<16>(mSolutionPattern) << "\n"
             << "current : " << std::bitset<16>(mCurrentPattern) << "\n"
             << "presses : " << mPressedCount << "\n"
             << "buttons : ";

        for (const auto& button : mButtons) {
            cout << "(" << std::bitset<16>(button) << ") ";
        }
        cout << "\n------------------\n";
    }

private:
    static u16 ParseLights(const std::string& input) {
        // for this problem we know there's never more than 16 lights
        u16 pattern = 0;
        for (i64 i = 1; i < input.find_first_of(']'); ++i) {
            if (input.at(i) == '#') {
                pattern |= 1 << (i - 1);
            }
        }

        return pattern;
    }

    static std::vector<u16> ParseButtons(const std::string& input) {
        std::vector<u16> buttons;
        buttons.reserve(10);
        for (i64 i = input.find_first_of('(') + 1; i < input.find_first_of('{') - 1;) {
            i64 length = input.find_first_of(')', i) - i;
            u16 button = 0;
            for (const auto& value : split(input.substr(i, length), ',')) {
                button |= 1 << std::stoll(value);
            }

            buttons.push_back(button);
            i += length + 3;
        }

        return buttons;
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
                machine.pressButton(pattern[i]);
            }

            if (machine.isSolved()) {
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

    for (auto& machine : machines) {
        sumOfMinPresses += brute_force_solve(machine);
    }

    return sumOfMinPresses;
}

int main() {
    // auto content = read_file("puzzle-10/test-input.txt");
    auto content = read_file("puzzle-10/input.txt");

    std::vector<Machine> machines;
    for (const auto& line : split(content, '\n')) {
        machines.emplace_back(line);
    }

    i64 solution = solve_machines(machines);

    cout << "solution: " << solution << "\n";
}
