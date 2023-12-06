#include <ranges>
#include <map>

#include "utils.h"
#include "AdventSolution02.h"

constexpr auto SET_DELIMITER = ';';
constexpr auto RED_LIMIT = 12;
constexpr auto GREEN_LIMIT = 13;
constexpr auto BLUE_LIMIT = 14;

enum Color {
    red,
    green,
    blue
};

struct Cubes {
    void add(Color color, int amount) {
        switch (color) {
        case Color::red:
            red += amount;
            break;
        case Color::green:
            green += amount;
            break;
        case Color::blue:
            blue += amount;
            break;
        }
    }

    bool isImpossible() const {
        return red > RED_LIMIT || green > GREEN_LIMIT || blue > BLUE_LIMIT;
    }

    int red = 0;
    int green = 0;
    int blue = 0;
};

int getGameId(std::string_view line) {
    int result = 0;

    auto itr = std::find(line.begin(), line.end(), ':');
    --itr;
    int digitPos = 0;

    while (charIsDigit(*itr)) {
        result += (*itr - ASCII_ZERO) * static_cast<int>(std::pow(10, digitPos));
        ++digitPos;
        --itr;
    }

    return result;
}

void AdventSolution02::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input02.txt");
    if (!input) {
        return;
    }

    int possibleGameIdSum = 0;
    int combinedSetPower = 0;

    for (const auto& str : std::views::split(input.value(), NEWLINE_DELIMITER)) {
        auto line = std::string_view(str);
        auto const gameId = getGameId(line);
        bool impossible = false;

        const auto gameIdDigitCount = std::to_string(gameId).size();

        // The prefix has 6 characters + the gameId digit count
        line.remove_prefix(gameIdDigitCount + 6);

        std::vector<Cubes> cubes_sets {};

        for (const auto& set_data_range : std::views::split(line, SET_DELIMITER)) {
            Cubes cubes;
            auto set_data = std::string_view(set_data_range);

            // Reverse iterate over the string
            auto itr = set_data.rbegin();

            Color color {};
            int current_digit_count = 0;
            int current_number = 0;
            bool is_reading_number = false;

            while (itr < set_data.rend()) {
                auto character = *itr;

                // Skip whitespace and commas
                if (character == ' ' || character == ',') {
                    itr++;

                    if (is_reading_number) {
                        cubes.add(color, current_number);
                    }

                    is_reading_number = false;
                    current_number = 0;
                    current_digit_count = 0;
                    continue;
                }

                if (charIsLetter(character)) {
                    if (is_reading_number) {
                        cubes.add(color, current_number);
                    }

                    is_reading_number = false;
                    current_number = 0;
                    current_digit_count = 0;

                    // Detect color by their last letter (string has been reversed)
                    if (character == 'd') {
                        color = Color::red;
                        itr += 3;
                    }
                    else if (character == 'n') {
                        color = Color::green;
                        itr += 5;
                    }
                    else if (character == 'e') {
                        color = Color::blue;
                        itr += 4;
                    }
                    else {
                        std::cerr << "[ERROR] [AdventSolution02] Invalid color character: " << character << std::endl;
                        return;
                    }
                }

                if (charIsDigit(character)) {
                    is_reading_number = true;
                    int num = character - ASCII_ZERO;
                    current_number += num * static_cast<int>(std::pow(10, current_digit_count));
                    current_digit_count++;
                    itr++;
                }
            }

            if (cubes.isImpossible()) {
                impossible = true;
            }

            cubes_sets.push_back(cubes);
        }

        if (!impossible) {
            possibleGameIdSum += gameId;
        }

        Cubes highestCubes;
        for (Cubes& cubes : cubes_sets) {
            if (cubes.red > highestCubes.red) {
                highestCubes.red = cubes.red;
            }
            if (cubes.green > highestCubes.green) {
                highestCubes.green = cubes.green;
            }
            if (cubes.blue > highestCubes.blue) {
                highestCubes.blue = cubes.blue;
            }
        }
        combinedSetPower += highestCubes.red * highestCubes.green * highestCubes.blue;
    }

    std::cout << "Task 1 - Possible Game ID Sum: " << possibleGameIdSum << std::endl;

    std::cout << "Task 2 - Combined Set Power: " << combinedSetPower << std::endl;

    end_ = std::chrono::high_resolution_clock::now();
}
