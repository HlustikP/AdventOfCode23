#include <ranges>
#include <numeric>

#include "utils.h"
#include "AdventSolution06.h"

void AdventSolution06::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input06.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();

    const auto line_end = std::find(input_string.begin(), input_string.end(), NEWLINE_DELIMITER);
    const auto race_times = get_numbers_from_string(std::string_view(input_string.begin(), line_end));
    const auto race_distances = get_numbers_from_string(std::string_view(line_end, input_string.end()));
    std::vector<int> ways_to_beat_record {};

    for (auto i = 0; i < race_times.size(); i++) {
        const auto race_time = race_times.at(i);
        const auto race_distance = race_distances.at(i);

        int button_hold_time = 0;
        int min_hold_time_to_succeed = 0;
        int max_hold_time_to_succeed = 0;

        // lower limit
        while (true) {
            const auto sail_time = race_time - button_hold_time;
            const auto traveled_distance = sail_time * button_hold_time;

            if (traveled_distance > race_distance) {
                min_hold_time_to_succeed = button_hold_time;
                break;
            }

            button_hold_time++;
        }

        // upper limit
        button_hold_time = race_time;
        while (true) {
            const auto sail_time = race_time - button_hold_time;
            const auto traveled_distance = sail_time * button_hold_time;

            if (traveled_distance > race_distance) {
                max_hold_time_to_succeed = button_hold_time;
                break;
            }

            button_hold_time--;
        }

        ways_to_beat_record.push_back(max_hold_time_to_succeed - min_hold_time_to_succeed + 1);
    }

    int multiplied_ways_to_beat_record = std::reduce(ways_to_beat_record.begin(), ways_to_beat_record.end(), 1, std::multiplies<int>());

    auto skip_chars = std::array<char, 1>{ ' ' };
    const int64_t real_race_time = get_numbers_from_string<int64_t>(std::string_view(input_string.begin(), line_end), skip_chars)[0];
    const int64_t real_race_distance = get_numbers_from_string<int64_t>(std::string_view(line_end, input_string.end()), skip_chars)[0];

    int button_hold_time = 0;
    int min_hold_time_to_succeed = 0;
    int max_hold_time_to_succeed = 0;

    // lower limit
    while (true) {
        const auto sail_time = real_race_time - button_hold_time;
        const auto traveled_distance = sail_time * button_hold_time;

        if (traveled_distance > real_race_distance) {
            min_hold_time_to_succeed = button_hold_time;
            break;
        }

        button_hold_time++;
    }

    // upper limit
    button_hold_time = real_race_time;
    while (true) {
        const auto sail_time = real_race_time - button_hold_time;
        const auto traveled_distance = sail_time * button_hold_time;

        if (traveled_distance > real_race_distance) {
            max_hold_time_to_succeed = button_hold_time;
            break;
        }

        button_hold_time--;
    }

    int real_race_time_to_succeed = max_hold_time_to_succeed - min_hold_time_to_succeed + 1;

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Multiplied ways to beat the record: " << multiplied_ways_to_beat_record << std::endl;
    std::cout << "Task 2 - Real race ways to beat the record " << real_race_time_to_succeed << std::endl;
}
