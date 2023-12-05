#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <algorithm>
#include <numeric>

namespace fs = std::filesystem;

constexpr auto DELIMITER = '\n';
constexpr auto ASCII_ZERO = 48;
constexpr auto ASCII_NINE = 57;
constexpr std::array DIGIT_WORDS = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

std::optional<std::string> readFile(const fs::path& path) {
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

int getLineCount(const std::string& input) {
    int count = 0;
    for (const auto& c : input) {
        if (c == '\n') {
            ++count;
        }
    }

    return count;
}

int parseLinePart1(const std::string_view line) {
    int result = 0;

    for (const auto& c : line) {
        if (c <= ASCII_NINE && c >= ASCII_ZERO) {
            result = (c - ASCII_ZERO) * 10;
            break;
        }
    }

    for (const auto& c : std::ranges::reverse_view(line)) {
        if (c <= ASCII_NINE && c >= ASCII_ZERO) {
            result += c - ASCII_ZERO;
            break;
        }
    }

    std::cout << "Parsed line: " << result << std::endl;

    return result;
}

int parseLinePart2(const std::string_view line) {
    int result = 0;

    for (const auto& c : line) {
        if (c <= ASCII_NINE && c >= ASCII_ZERO) {
            result = (c - ASCII_ZERO) * 10;
            break;
        }
    }

    for (const auto& c : std::ranges::reverse_view(line)) {
        if (c <= ASCII_NINE && c >= ASCII_ZERO) {
            result += c - ASCII_ZERO;
            break;
        }
    }

    std::cout << "Parsed line: " << result << std::endl;

    return result;
}

int main() {
    std::cout << "AdventOfCode23-1" << std::endl;

    const auto input = readFile("input.txt");
    if (!input) {
        return 1;
    }

    const auto line_count = getLineCount(input.value()) + 1;
    std::cout << "Input line count: " << line_count << std::endl;

    std::vector<int> numbers;
    numbers.reserve(line_count);

    std::cout << "Part 1 Solution:" << std::endl;

    for (const auto& str : std::views::split(input.value(), DELIMITER)) {
        numbers.push_back(parseLinePart1(std::string_view(str)));
    }

    auto const sum = std::reduce(numbers.begin(), numbers.end());

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
