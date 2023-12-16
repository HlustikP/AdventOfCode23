#pragma once

#include "AdventSolution.h"

class AdventSolution16 : public AdventSolution {
public:
    AdventSolution16() : AdventSolution(fs::path("input16.txt"), "Advent of Code 16 - The Floor Will Be Lava") {};

    void solve() override;
};
