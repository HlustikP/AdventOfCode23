#include <array>
#include <vector>
#include <ranges>
#include <string>
#include <algorithm>
#include <numeric>
#include <chrono>

#include "utils.h"
#include "AdventSolution01.h"

constexpr auto DELIMITER = '\n';
constexpr std::array DIGIT_WORDS = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
constexpr std::array DIGIT_WORDS_REVERSED = { "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin" };

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

    return result;
}

int parseLinePart2(const std::string_view line) {
    int result = 0;
    int i = 0;
    const auto line_size = line.size();

    for (const auto& c : line) {
        if (c <= ASCII_NINE && c >= ASCII_ZERO) {
            result = (c - ASCII_ZERO) * 10;
            break;
        }

        bool result_found = false;

        for (const auto word : DIGIT_WORDS) {
            if (strlen(word) + i > line_size) {
                continue;
            }

            if (std::equal(word, word + strlen(word), line.begin() + i)) {
                result = static_cast<int>(
                    std::distance(DIGIT_WORDS.begin(), std::find(DIGIT_WORDS.begin(), DIGIT_WORDS.end(), word)) + 1) * 10;
                result_found = true;
                break;
            }
        }

        if (result_found) {
            break;
        }

        ++i;
    }

    i = 0;

    for (const auto& c : std::ranges::reverse_view(line)) {
        if (c <= ASCII_NINE && c >= ASCII_ZERO) {
            result += c - ASCII_ZERO;
            break;
        }

        bool result_found = false;

        for (const auto word : DIGIT_WORDS_REVERSED) {
            if (strlen(word) + i > line_size) {
                continue;
            }

            if (std::equal(word, word + strlen(word), line.rbegin() + i)) {
                result += static_cast<int>(
                    std::distance(DIGIT_WORDS_REVERSED.begin(), std::find(DIGIT_WORDS_REVERSED.begin(), DIGIT_WORDS_REVERSED.end(), word)) + 1);
                result_found = true;
                break;
            }
        }

        if (result_found) {
            break;
        }

        ++i;
    }

    return result;
}

void AdventSolution01::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input01.txt");
    if (!input) {
        return;
    }

    const auto line_count = getLineCount(input.value()) + 1;

    std::vector<int> numbers1;
    std::vector<int> numbers2;
    numbers1.reserve(line_count);
    numbers2.reserve(line_count);

    for (const auto& str : std::views::split(input.value(), DELIMITER)) {
        numbers1.push_back(parseLinePart1(std::string_view(str)));
        numbers2.push_back(parseLinePart2(std::string_view(str)));
    }

    auto const sum1 = std::reduce(numbers1.begin(), numbers1.end());
    auto const sum2 = std::reduce(numbers2.begin(), numbers2.end());

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Sum 1: " << sum1 << std::endl;
    std::cout << "Sum 2: " << sum2 << std::endl;
}
