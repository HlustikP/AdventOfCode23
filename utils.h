#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace fs = std::filesystem;

constexpr auto NEWLINE_DELIMITER = '\n';

constexpr auto ASCII_ZERO = 48;
constexpr auto ASCII_NINE = 57;

inline std::optional<std::string> readFile(const fs::path& path) {
    if (!fs::exists(path)) {
        std::cerr << "[ERROR] [FILE] " << path << " does not exist" << std::endl;
        return std::nullopt;
    }

    try {
        std::ifstream f(path, std::ios::in | std::ios::binary);
        const auto size = fs::file_size(path);
        std::string result(size, '\0');
        f.read(result.data(), static_cast<std::streamsize>(size));

        return result;
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] [FILE] " << e.what() << std::endl;
        return std::nullopt;
    }
}

inline bool charIsDigit(const char c) {
    return c <= '9' && c >= '0';
}

inline bool charIsLetter(const char c) {
    return (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A');
}

template <typename T>
bool itr_is_first_line(T itr_begin, T itr_current, int line_size) {
    return std::distance(itr_begin, itr_current) < line_size;
}

template <typename T>
bool itr_is_last_line(T itr_begin, T itr_current, int line_size, int line_count) {
    return std::distance(itr_begin, itr_current) >= line_size * (line_count - 1);
}

template <typename T>
bool itr_is_first_column(T itr_begin, T itr_current, int line_size) {
    return std::distance(itr_begin, itr_current) % line_size == 0;
}

template <typename T>
bool itr_is_last_column(T itr_begin, T itr_current, int line_size) {
    return std::distance(itr_begin, itr_current) % line_size == line_size - 1;
}
