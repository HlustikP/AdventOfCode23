#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>

namespace fs = std::filesystem;

class AdventSolution {
public:
    AdventSolution(const fs::path& input, std::string headline) : headline_{ headline }, input_{ input } {};
    virtual ~AdventSolution() = default;

    void printHeadline() const {
        std::cout << '\n' << headline_ << std::endl;
    }

    void printTime() const {
        std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count() << "us" << std::endl;
    }

    virtual void solve() = 0;

    inline static std::vector<std::unique_ptr<AdventSolution>> solutions {};
protected:
    std::string headline_ {};
    fs::path input_ {};
    std::chrono::high_resolution_clock::time_point start_ {};
    std::chrono::high_resolution_clock::time_point end_ {};
};
