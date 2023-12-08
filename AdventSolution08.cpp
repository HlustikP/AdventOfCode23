#include <ranges>
#include <map>

#include "utils.h"
#include "AdventSolution08.h"
#include <numeric>

constexpr auto INSTRUCTION_LINE_SIZE = 16;
constexpr auto LEFT_INSTRUCTION_START = 7;
constexpr auto RIGHT_INSTRUCTION_START = 12;
constexpr std::string_view START = "AAA";
constexpr std::string_view END = "ZZZ";

struct Directions {
    std::string left;
    std::string right;
};

void AdventSolution08::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input08.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();
    std::string directions {};
    std::map<std::string_view, Directions> instructions;

    for (const auto& str : std::views::split(input_string, NEWLINE_DELIMITER)) {
        const std::string_view line(str);

        // skip empty lines
        if (line.empty()) {
            continue;
        }

        // if the line is not an instruction, its the direction map
        if (line.size() != INSTRUCTION_LINE_SIZE) {
            auto size = line.size();
            directions = line;
            continue;
        }

        instructions.emplace(line.substr(0, 3), Directions{ 
            std::string(line.substr(LEFT_INSTRUCTION_START, 3)), std::string(line.substr(RIGHT_INSTRUCTION_START, 3)) });
    }

    auto current_position = START;
    int steps = 0;

    // part 1
    while(current_position != END) {
        for (const auto& direction : directions) {
            if (current_position == END) {
                break;
            }

            auto& next_directions = instructions[current_position];
            current_position = direction == 'L' ? next_directions.left : next_directions.right;
            steps++;
        }
    }

    // part 2
    std::vector<std::string_view> current_positions;
    // add all instructions keys to the current positions that end with an A
    for (const auto& [key, _] : instructions) {
        if (key.ends_with('A')) {
            current_positions.push_back(key);
        }
    }
    // Advance all current positions until theyre all at a __Z position and pray that it loops from there
    for (auto& current_position : current_positions) {
        while (!current_position.ends_with('Z')) {
            for (const auto& direction : directions) {
                if (current_position.ends_with('Z')) {
                    break;
                }

                auto& next_directions = instructions[current_position];
                current_position = direction == 'L' ? next_directions.left : next_directions.right;
            }
        }
    }
    std::vector<int64_t> loop_sizes {};
    std::vector<std::string_view> loop_starts = current_positions;
    // Seek out the loop counts
    for (auto i = 0; i < current_positions.size(); i++) {
        auto& current_position = current_positions[i];
        auto& loop_start = loop_starts[i];
        auto loop_size = 0;
        bool fully_looped = false;
        while (!fully_looped) {
            for (const auto& direction : directions) {
                auto& next_directions = instructions[current_position];
                current_position = direction == 'L' ? next_directions.left : next_directions.right;
                loop_size++;

                if (current_position == loop_start) {
                    fully_looped = true;
                    break;
                }
            }
        }
        loop_sizes.push_back(loop_size);
    }

    // int64 needed because int32 overflows
    const int64_t ghost_steps = std::accumulate(loop_sizes.begin(), loop_sizes.end(), 1ll, [](int64_t a, int64_t b){
        return std::lcm<int64_t, int64_t>(a, b);
    });

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Number of steps to take: " << steps << std::endl;
    std::cout << "Task 2 - Number of ghost steps: " << ghost_steps << std::endl;
}
