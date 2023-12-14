#pragma once

#include "AdventSolution.h"

class AdventSolution11 : public AdventSolution {
public:
    AdventSolution11() : AdventSolution(fs::path("input11.txt"), "Advent of Code 11 - Cosmic Expansion") {};

    void solve() override;
};
