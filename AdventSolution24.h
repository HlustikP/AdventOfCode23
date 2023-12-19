#pragma once

#include "AdventSolution.h"

class AdventSolution24 : public AdventSolution {
public:
    AdventSolution24() : AdventSolution(fs::path("input24.txt"), "Advent of Code 24 - ") {};

    void solve() override;
};
