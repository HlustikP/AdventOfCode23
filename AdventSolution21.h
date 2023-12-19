#pragma once

#include "AdventSolution.h"

class AdventSolution21 : public AdventSolution {
public:
    AdventSolution21() : AdventSolution(fs::path("input21.txt"), "Advent of Code 21 - ") {};

    void solve() override;
};
