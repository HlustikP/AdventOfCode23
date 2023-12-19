#pragma once

#include "AdventSolution.h"

class AdventSolution18 : public AdventSolution {
public:
    AdventSolution18() : AdventSolution(fs::path("input18.txt"), "Advent of Code 18 - ") {};

    void solve() override;
};
