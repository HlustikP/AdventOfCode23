#pragma once

#include "AdventSolution.h"

class AdventSolution10 : public AdventSolution {
public:
    AdventSolution10() : AdventSolution(fs::path("input10.txt"), "Advent of Code 10 - Pipe Maze") {};

    void solve() override;
};
