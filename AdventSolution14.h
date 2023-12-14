#pragma once

#include "AdventSolution.h"

class AdventSolution14 : public AdventSolution {
public:
    AdventSolution14() : AdventSolution(fs::path("input14.txt"), "Advent of Code 14 - Parabolic Reflector Dish") {};

    void solve() override;
};
