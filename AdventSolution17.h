#pragma once

#include "AdventSolution.h"

class AdventSolution17 : public AdventSolution {
public:
    AdventSolution17() : AdventSolution(fs::path("input17.txt"), "Advent of Code 17 - ") {};

    void solve() override;
};
