#pragma once

#include "AdventSolution.h"

class AdventSolution15 : public AdventSolution {
public:
    AdventSolution15() : AdventSolution(fs::path("input15.txt"), "Advent of Code 15 - Lens Library") {};

    void solve() override;
};
