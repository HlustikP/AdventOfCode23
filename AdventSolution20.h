#pragma once

#include "AdventSolution.h"

class AdventSolution20 : public AdventSolution {
public:
    AdventSolution20() : AdventSolution(fs::path("input20.txt"), "Advent of Code 20 - ") {};

    void solve() override;
};
