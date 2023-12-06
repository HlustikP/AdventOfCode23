#include <ranges>

#include "utils.h"
#include "AdventSolution03.h"

void AdventSolution03::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input03.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();
    const int line_size = static_cast<int>(
        std::distance(input_string.begin(), std::find(input_string.begin(), input_string.end(), NEWLINE_DELIMITER)) + 1);
    const int line_count = static_cast<int>(input_string.size() / line_size);

    int current_number = -1;
    int current_digit = 0;
    int sum = 0;
    // right hand side border of current number
    auto num_rhs = input_string.rend();

    const auto reset = [&]() {
        current_number = -1;
        current_digit = 0;
        num_rhs = input_string.rend();
    };

    const auto is_special_character = [](char c) {
        return !charIsDigit(c) && c != '.';
    };

    const auto check_in_range = [&](auto begin, auto end, int offset) {
        auto itr = begin;
        while (itr <= end) {
            if (is_special_character(*(itr + offset))) {
                return true;
            }
            itr++;
        }
        return false;
    };

    const auto has_adjacent_special_character = [&](auto itr_num_begin, auto itr_num_end) {
        int check_diagonally_left = 0;
        int check_diagonally_right = 0;

        // Check character before
        if (!itr_is_first_column(input_string.rbegin(), itr_num_begin, line_size)) {
            if (is_special_character(*(itr_num_begin - 1))) {
                return true;
            }
            check_diagonally_left = -1;
        }

        // Check character after
        if (!itr_is_last_column(input_string.rbegin(), itr_num_end, line_size)) {
            if (is_special_character(*(itr_num_end + 1))) {
                return true;
            }
            check_diagonally_right = 1;
        }

        // Check characters above
        if (!itr_is_first_line(input_string.rbegin(), itr_num_begin, line_size)) {
            if (check_in_range(itr_num_begin + check_diagonally_left, itr_num_end + check_diagonally_right, -line_size)) {
                return true;
            }
        }

        // Check characters below
        if (!itr_is_last_line(input_string.rbegin(), itr_num_end, line_size, line_count)) {
            if (check_in_range(itr_num_begin + check_diagonally_left, itr_num_end + check_diagonally_right, +line_size)) {
                return true;
            }
        }

        return false;
    };

    const auto add_number_to_sum = [&]() {
        if (!has_adjacent_special_character(num_rhs, num_rhs + current_digit - 1)) {
            reset();
            return;
        }

        sum += current_number;
        reset();
    };

    for (auto itr = input_string.rbegin(); itr < input_string.rend(); itr++) {
        if (*itr == NEWLINE_DELIMITER) {
            if (current_number != -1) {
                add_number_to_sum();
            }
            continue;
        }

        if (charIsDigit(*itr)) {
            if (current_number == -1) {
                current_number = 0;
                num_rhs = itr;
            }

            current_number += (*itr - ASCII_ZERO) * static_cast<int>(std::pow(10, current_digit));
            current_digit++;
            continue;
        }

        if (current_number != -1) {
            add_number_to_sum();
        }
    }

    if (current_number != -1) {
        add_number_to_sum();
    }

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Engine Schematic Sum: " << sum << std::endl;
    std::cout << "Task 2: " << std::endl;
}
