#pragma once

#include "AdventSolution.h"

class AdventSolution07 : public AdventSolution {
public:
    AdventSolution07() : AdventSolution(fs::path("input07.txt"), "Advent of Code 07 - Camel Cards") {};

    void solve() override;
};
