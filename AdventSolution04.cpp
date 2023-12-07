#include <ranges>

#include "utils.h"
#include "AdventSolution04.h"

void AdventSolution04::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input04.txt");
    if (!input) {
        return;
    }

    for (const auto& str : std::views::split(input.value(), NEWLINE_DELIMITER)) {
        auto line = std::string_view(str);
        auto const segment_1_start = std::find(line.begin(), line.end(), ':');
        const auto pipe_itr = std::find(line.begin(), line.end(), '|');
    }

    const auto& input_string = input.value();

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1: " << std::endl;
    std::cout << "Task 2: " << std::endl;
}
