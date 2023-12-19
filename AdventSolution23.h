#pragma once

#include "AdventSolution.h"

class AdventSolution23 : public AdventSolution {
public:
    AdventSolution23() : AdventSolution(fs::path("input23.txt"), "Advent of Code 23 - ") {};

    void solve() override;
};
