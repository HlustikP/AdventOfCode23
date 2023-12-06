#include "AdventSolution.h"
#include "AdventSolution01.h"
#include "AdventSolution02.h"

int main() {
    std::cout << "AdventOfCode23" << std::endl;

    AdventSolution::solutions.push_back(std::make_unique<AdventSolution01>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution02>());

    const auto start = std::chrono::high_resolution_clock::now();

    for (auto& solution : AdventSolution::solutions) {
        solution->printHeadline();
        solution->solve();
        solution->printTime();
    }

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nTotal Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    return 0;
}
