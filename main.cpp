#include "AdventSolution.h"
#include "AdventSolution01.h"
#include "AdventSolution02.h"
#include "AdventSolution03.h"
#include "AdventSolution04.h"
#include "AdventSolution05.h"
#include "AdventSolution06.h"
#include "AdventSolution07.h"
#include "AdventSolution08.h"
#include "AdventSolution09.h"
#include "AdventSolution10.h"
#include "AdventSolution11.h"
#include "AdventSolution12.h"
#include "AdventSolution13.h"
#include "AdventSolution14.h"
#include "AdventSolution15.h"
#include "AdventSolution16.h"

int main() {
    std::cout << "AdventOfCode23" << std::endl;

    AdventSolution::solutions.push_back(std::make_unique<AdventSolution01>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution02>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution03>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution04>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution05>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution06>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution07>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution08>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution09>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution10>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution11>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution12>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution13>());
    //AdventSolution::solutions.push_back(std::make_unique<AdventSolution14>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution15>());
    AdventSolution::solutions.push_back(std::make_unique<AdventSolution16>());

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
