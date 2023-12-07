#pragma once

#include "AdventSolution.h"

class AdventSolution05 : public AdventSolution {
public:
    AdventSolution05() : AdventSolution(fs::path("input05.txt"), "Advent of Code 05 - If You Give A Seed A Fertilizer") {};

    void solve() override;
};
