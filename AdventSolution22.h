#pragma once

#include "AdventSolution.h"

class AdventSolution22 : public AdventSolution {
public:
    AdventSolution22() : AdventSolution(fs::path("input22.txt"), "Advent of Code 22 - ") {};

    void solve() override;
};
