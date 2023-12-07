#include <ranges>

#include "utils.h"
#include "AdventSolution06.h"

void AdventSolution06::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input06.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1: " << std::endl;
    std::cout << "Task 2: " << std::endl;
}
