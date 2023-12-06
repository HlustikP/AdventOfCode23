#pragma once

#include "AdventSolution.h"

class AdventSolution02 : public AdventSolution {
public:
    AdventSolution02() : AdventSolution(fs::path("input02.txt"), "Advent of Code 02 - Cube Conundrum") {};

    void solve() override;
};
