#include <ranges>
#include <set>

#include "utils.h"
#include "AdventSolution14.h"

constexpr char MIRROR_CHAR = 'O';
constexpr char EMPTY_CHAR = '.';
constexpr char WALL_CHAR = '#';
constexpr int64_t CYCLE_COUNT = 1000000000;

static void move_mirror_up(std::string& input, const size_t line_size, std::string::iterator mirror_itr) {
    if (std::distance(input.begin(), mirror_itr) < line_size) {
        return;
    }

    auto char_above = mirror_itr - line_size;
    if (*char_above == WALL_CHAR) {
        return;
    }

    if (*char_above == EMPTY_CHAR) {
        std::swap(*mirror_itr, *char_above);
    }

    move_mirror_up(input, line_size, char_above);
}

static void move_mirror_down(std::string& input, const size_t line_size, std::string::reverse_iterator mirror_itr) {
    if (std::distance(input.rbegin(), mirror_itr) < line_size) {
        return;
    }

    auto char_below = mirror_itr - line_size;
    if (*char_below == WALL_CHAR) {
        return;
    }

    if (*char_below == EMPTY_CHAR) {
        std::swap(*mirror_itr, *char_below);
    }

    move_mirror_down(input, line_size, char_below);
}

static void move_mirror_left(std::string& input, const size_t line_size, std::string::iterator mirror_itr) {
    if (std::distance(input.begin(), mirror_itr) % line_size == line_size - 1) {
        return;
    }

    auto char_left = mirror_itr - 1;
    if (*char_left == WALL_CHAR) {
        return;
    }

    if (*char_left == EMPTY_CHAR) {
        std::swap(*mirror_itr, *char_left);
    }

    if (char_left < input.begin()) {
        return;
    }

    move_mirror_left(input, line_size, char_left);
}

static void move_mirror_right(std::string& input, const size_t line_size, std::string::reverse_iterator mirror_itr) {
    if (mirror_itr == input.rbegin()) {
        return;
    }

    auto char_right = mirror_itr -1;

    if (*char_right == WALL_CHAR || *char_right == NEWLINE_DELIMITER) {
        return;
    }

    if (*char_right == EMPTY_CHAR) {
        std::swap(*mirror_itr, *char_right);
    }

    move_mirror_right(input, line_size, char_right);
}

template <typename T>
bool contains(std::vector<T> const& vec, const T str) {
    return std::ranges::find(vec, str) != vec.end();
}

template <typename T>
bool contains_n(std::vector<T> const& vec, const T str, size_t amount) {
    auto hits = 0;
    for (auto const& elem : vec) {
        if (elem == str) {
            hits++;
        }
        if (hits == amount) {
            return true;
        }
    }
    return false;
}


void AdventSolution14::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    auto input = readFile("input14.txt");
    if (!input) {
        return;
    }

    auto& input_string = input.value();

    const auto line_size = input_string.find(NEWLINE_DELIMITER) + 1;
    const auto line_count = std::ranges::count(input_string, NEWLINE_DELIMITER) + 1;

    int total_weight_part1 = 0;
    int total_weight = 0;
    bool first_iteration = true;

    auto calculate_weight = [&input_string, line_size]() {
        int weight = 0;
        for (auto itr = input_string.rbegin(); itr < input_string.rend(); itr++) {
            if (*itr == MIRROR_CHAR) {
                weight += std::distance(input_string.rbegin(), itr) / line_size + 1;
            }
        }
        return weight;
    };

    std::vector<std::string> constellations {};

    for (int64_t i = 0; i < 4 * CYCLE_COUNT; i++) {
        if (i % 4 == 0 || i % 4 == 1) {
            for (auto itr = input_string.begin(); itr < input_string.end(); itr++) {
                if (*itr != MIRROR_CHAR) {
                    continue;
                }

                if (i % 4 == 0) {
                    move_mirror_up(input_string, line_size, itr);
                } else if (i % 4 == 1) {
                    move_mirror_left(input_string, line_size, itr);
                }

            }
            if (first_iteration) {
                total_weight_part1 = calculate_weight();
                first_iteration = false;
            }
        } else {
            for (auto itr = input_string.rbegin(); itr < input_string.rend(); itr++) {
                if (*itr != MIRROR_CHAR) {
                    continue;
                }

                if (i % 4 == 2) {
                    move_mirror_down(input_string, line_size, itr);
                } else if (i % 4 == 3) {
                    move_mirror_right(input_string, line_size, itr);
                }
            }
        }

        // if constellations contains input_string, we have found a cycle
        if (contains(constellations, input_string) && i % 4 == 3) {
            const int64_t pre_cycle = std::distance(constellations.begin(), std::find(constellations.begin(), constellations.end(), input_string));
            const int64_t cycle_length = std::distance(std::find(constellations.begin(), constellations.end(), input_string), constellations.end());
            
            std::cout << "Cycle began after iterations " << pre_cycle << std::endl;
            std::cout << "Cycle length: " << cycle_length << std::endl;

            const int64_t target_constellation = (CYCLE_COUNT + pre_cycle) % cycle_length;
            std::cout << "Target constellation: " << target_constellation << std::endl;
            input_string = constellations[target_constellation];

            break;
        }

        // full rotation
        if (i % 4 == 3) {
            constellations.push_back(input_string);
        }
    }

    total_weight = calculate_weight();

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Total weight: " << total_weight_part1 << std::endl;
    std::cout << "Task 2 - Total weight after 1 billion cycles (WIP): " << total_weight << std::endl;
}
