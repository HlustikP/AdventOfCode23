#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <algorithm>

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

inline std::optional<int> charDigitToInt(const char c) {
    if (!charIsDigit(c)) {
        return std::nullopt;
    }

    return c - ASCII_ZERO;
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

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (const auto& v : vec) {
        os << v << " ";
    }

    return os;
}

inline std::vector<int> get_numbers_from_string(std::string_view sv) {
    std::vector<int> numbers;
    int current_number = -1;
    int current_digit = 0;
    auto itr = sv.end() - 1;

    while (itr >= sv.begin()) {
        if (!charIsDigit(*itr)) {
            if (current_number > -1) {
                numbers.push_back(current_number);
                current_digit = 0;
                current_number = -1;
            }
        } else {
            if (const auto digit = charDigitToInt(*itr); digit.has_value()) {
                if (current_number == -1) {
                    current_number = 0;
                }

                current_number += digit.value() * static_cast<int>(std::pow(10, current_digit));
                current_digit++;
            }
        }

        if (itr == sv.begin()) [[unlikely]] {
            break;
        }
        itr--;
    }

    if (current_number > -1) {
        numbers.push_back(current_number);
    }

    return numbers;
};

template <typename T, size_t N>
inline std::vector<T> get_numbers_from_string(std::string_view sv, const std::array<char, N> skip_chars) {
    std::vector<T> numbers;
    T current_number = -1;
    T current_digit = 0;
    auto itr = sv.end() - 1;

    while (itr >= sv.begin()) {
        if (std::find(skip_chars.begin(), skip_chars.end(), *itr) != skip_chars.end()) {
            itr--;
            continue;
        }

        if (!charIsDigit(*itr)) {
            if (current_number > -1) {
                numbers.push_back(current_number);
                current_digit = 0;
                current_number = -1;
            }
        }
        else {
            if (const auto digit = charDigitToInt(*itr); digit.has_value()) {
                if (current_number == -1) {
                    current_number = 0;
                }

                current_number += digit.value() * static_cast<T>(std::pow(10, current_digit));
                current_digit++;
            }
        }

        if (itr == sv.begin()) [[unlikely]] {
            break;
            }
        itr--;
    }

    if (current_number > -1) {
        numbers.push_back(current_number);
    }

    return numbers;
};
