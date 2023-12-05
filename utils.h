#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace fs = std::filesystem;

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
