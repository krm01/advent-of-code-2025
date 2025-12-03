// utils.h
#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdint>
#include <concepts>
#include <vector>

using i8   = int8_t;
using u8   = uint8_t;
using i16  = int16_t;
using u16  = uint16_t;
using i32  = int32_t;
using u32  = uint32_t;
using i64  = int64_t;
using u64  = uint64_t;

using f32  = float;
using f64  = double;

extern const std::string RESULT_MARK[2];

std::string read_file(const std::string& path);
bool is_prime(i64 n);

template <typename T>
requires std::convertible_to<T, std::string> || std::same_as<T, char>
std::string repeat(const T& value, size_t n) {
    if constexpr (std::same_as<T, char>) {
        return std::string(n, value);
    } else {
        std::string ret;
        ret.reserve(value.size() * n);
        while (n--) {
            ret += value;
        }
        return ret;
    }
}

template <typename T>
requires std::convertible_to<T, std::string> || std::same_as<T, char>
std::vector<std::string> split(const std::string& value, const T& delimiter) {
    std::vector<std::string> parts;
    size_t pos = 0;
    size_t next = 0;
    std::string delim;

    if constexpr (std::same_as<T, char>) {
        delim = std::string(1, delimiter);
    } else {
        delim = delimiter;
    }
 
    while ((next = value.find(delim, pos)) != std::string::npos) {
        parts.emplace_back(value.substr(pos, next - pos));
        pos = next + delim.size();
    }

    // add the last token
    parts.emplace_back(value.substr(pos));

    return parts;
}
