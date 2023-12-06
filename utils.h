#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace fs = std::filesystem;

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
