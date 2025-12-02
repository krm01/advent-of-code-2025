#include "utils.h"

const std::string RESULT_MARK[2] = { "❌", "✅" };

std::string read_file(const std::string& path) {
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

bool is_prime(i64 n) {
    if (n <= 1) return false;   // 0, 1 no prime
    if (n <= 3) return true;    // 2, 3 yes prime

    if (((n % 2) == 0) || ((n % 3) == 0)) {
        return false; // number is even (or divisible by known prime, 3)
    }

    // 6k + 1 prime checking
    for (i64 i = 5; i * i < n; i += 6) {
        if (((n % i) == 0) || ((n % (i + 1)) == 0)) {
            return false;
        }
    }

    return true;
}
