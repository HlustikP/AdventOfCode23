#pragma once

#include "AdventSolution.h"

class AdventSolution25 : public AdventSolution {
public:
    AdventSolution25() : AdventSolution(fs::path("input25.txt"), "Advent of Code 25 - ") {};

    void solve() override;
};
