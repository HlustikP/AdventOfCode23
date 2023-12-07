#include <ranges>
#include <algorithm>
#include <functional>
#include <future>

#include "utils.h"
#include "AdventSolution04.h"

void AdventSolution04::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input04.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();
    int points = 0;
    std::atomic<int> total_cards = 0;

    std::vector<std::vector<int>> intersections_per_card;
    intersections_per_card.reserve(216);

    // part 1
    for (const auto& str : std::views::split(input_string, NEWLINE_DELIMITER)) {
        auto line = std::string_view(str);
        auto const segment_1_start = std::find(line.begin(), line.end(), ':');
        const auto pipe_itr = std::find(line.begin(), line.end(), '|');

        std::vector<int> winning_numbers;
        winning_numbers.reserve(10);
        int current_number = 0;
        int current_digit = 0;
        auto itr = pipe_itr;

        while (itr > segment_1_start) {
            if (*itr == ' ') {
                if (current_digit > 0) {
                    winning_numbers.push_back(current_number);
                    current_digit = 0;
                    current_number = 0;
                }
            } else {
                if (const auto digit = charDigitToInt(*itr); digit.has_value()) {
                    current_number += digit.value() * static_cast<int>(std::pow(10, current_digit));
                    current_digit++;
                }
            }
            --itr;
        }

        std::vector<int> chosen_numbers;
        chosen_numbers.reserve(25);
        current_number = 0;
        current_digit = 0;
        itr = line.end() - 1;

        while (itr > pipe_itr) {
            if (*itr == ' ') {
                if (current_digit > 0) {
                    chosen_numbers.push_back(current_number);
                    current_digit = 0;
                    current_number = 0;
                }
            }
            else {
                if (const auto digit = charDigitToInt(*itr); digit.has_value()) {
                    current_number += digit.value() * static_cast<int>(std::pow(10, current_digit));
                    current_digit++;
                }
            }
            --itr;
        }

        std::vector<int> intersections;
        // Sort to use std::set_intersection
        std::sort(winning_numbers.begin(), winning_numbers.end());
        std::sort(chosen_numbers.begin(), chosen_numbers.end());
        // Find intersections and store in intersections vector
        std::set_intersection(winning_numbers.begin(), winning_numbers.end(), chosen_numbers.begin(), chosen_numbers.end(), std::back_inserter(intersections));

        intersections_per_card.push_back(intersections);
        points += static_cast<int>(std::pow(2, intersections.size() - 1));
    }

    std::function<void(int)> traverse_cards;
    traverse_cards = [&total_cards, &traverse_cards, &intersections_per_card](int card) {
        total_cards++;
        const auto& next_cards = intersections_per_card[card - 1];
        for (auto i = 0; i < next_cards.size(); i++) {
            traverse_cards(card + i + 1);
        }
    };

    auto promise_lower_half = std::async(std::launch::async, [&total_cards, &traverse_cards, &intersections_per_card](){
        for (auto i = 1; i < 106; i++) {
            traverse_cards(i);
        }
    });
    auto promise_upper_half = std::async(std::launch::async, [&total_cards, &traverse_cards, &intersections_per_card]() {
        for (auto i = 106; i < 217; i++) {
            traverse_cards(i);
        }
    });

    promise_lower_half.wait();
    promise_upper_half.wait();

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Total Points: " << points << std::endl;
    std::cout << "Task 2 - Total Scratchcards: " << total_cards << std::endl;
}
