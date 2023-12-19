#pragma once

#include "AdventSolution.h"

class AdventSolution13 : public AdventSolution {
public:
    AdventSolution13() : AdventSolution(fs::path("input12.txt"), "Advent of Code 13 - Point of Incidence") {};

    void solve() override;
};
