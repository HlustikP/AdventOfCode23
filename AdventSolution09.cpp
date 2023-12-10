#include <ranges>

#include "utils.h"
#include "AdventSolution09.h"

static int find_next_value_in_sequence(const std::vector<int>& nums) {
    if (nums.size() == 1) {
        return nums[0];
    }

    // Derivation is 0 if all numbers are equal
    if (std::all_of(nums.begin(), nums.end(), [&nums](auto element) { return element == nums[0]; })) {
        return nums[0];
    }

    std::vector<int> derivation;
    derivation.reserve(nums.size() - 1);

    for (auto i = 0; i < nums.size() - 1; i++) {
        derivation.push_back(nums[i + 1] - nums[i]);
    }

    auto next_value = find_next_value_in_sequence(derivation);
    return nums.back() + next_value;
}

void AdventSolution09::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input09.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();
    int64_t part1_result = 0;
    int64_t part2_result = 0;

    for (const auto& str : std::views::split(input_string, NEWLINE_DELIMITER)) {
        std::string_view line(str);

        auto numbers = get_numbers_from_string(line);
        auto previous_number = find_next_value_in_sequence(numbers);
        part2_result += previous_number;
        std::reverse(numbers.begin(), numbers.end());

        auto next_number = find_next_value_in_sequence(numbers);
        part1_result += next_number;
    }

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Sum of next numbers: " << part1_result << std::endl;
    std::cout << "Task 2 - Sum of previous numbers: " << part2_result << std::endl;
}
