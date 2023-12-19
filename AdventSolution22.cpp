#include <ranges>

#include "utils.h"
#include "AdventSolution22.h"

void AdventSolution22::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile(input_);
    if (!input) {
        return;
    }

    const auto& input_string = input.value();

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - : " << std::endl;
    std::cout << "Task 2 - : " << std::endl;
}
