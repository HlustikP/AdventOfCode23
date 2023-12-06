#pragma once

#include "AdventSolution.h"

class AdventSolution01 : public AdventSolution {
public:
    AdventSolution01() : AdventSolution(fs::path("input01.txt"), "Advent of Code 01 - Trebuchet?!") {};

    void solve() override;
};
