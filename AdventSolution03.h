#pragma once

#include "AdventSolution.h"

class AdventSolution03 : public AdventSolution {
public:
    AdventSolution03() : AdventSolution(fs::path("input03.txt"), "Advent of Code 03 - Gear Ratios") {};

    void solve() override;
};
