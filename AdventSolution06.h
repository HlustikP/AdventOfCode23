#pragma once

#include "AdventSolution.h"

class AdventSolution06 : public AdventSolution {
public:
    AdventSolution06() : AdventSolution(fs::path("input06.txt"), "Advent of Code 06 - Wait For It") {};

    void solve() override;
};
