#include <ranges>

#include "utils.h"
#include "AdventSolution05.h"

void AdventSolution05::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input05.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1: " << "WIP" << std::endl;
    std::cout << "Task 2: " << "WIP" << std::endl;
}
