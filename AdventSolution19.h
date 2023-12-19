#pragma once

#include "AdventSolution.h"

class AdventSolution19 : public AdventSolution {
public:
    AdventSolution19() : AdventSolution(fs::path("input19.txt"), "Advent of Code 19 - ") {};

    void solve() override;
};
