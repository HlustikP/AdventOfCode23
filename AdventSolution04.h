#pragma once

#include "AdventSolution.h"

class AdventSolution04 : public AdventSolution {
public:
    AdventSolution04() : AdventSolution(fs::path("input04.txt"), "Advent of Code 04 - Scratchcards") {};

    void solve() override;
};
