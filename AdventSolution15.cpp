#include <ranges>
#include <numeric>

#include "utils.h"
#include "AdventSolution15.h"

struct Lens {
    Lens(std::string_view label, int focal_length) : label(label), focal_length(focal_length) {};

    std::string_view label {};
    int focal_length {};

    bool operator==(const Lens& other) const {
        return label == other.label;
    }
};

void AdventSolution15::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input15.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();

    std::vector<unsigned char> part1_hashes {};
    part1_hashes.reserve(std::count(input_string.begin(), input_string.end(), ',') + 1);

    int part2_result = 0;
    std::vector<std::vector<Lens>> part2_hashmap(256);

    auto calculate_hash = [](std::string_view view) {
        unsigned char hash = 0;
        for (auto const& c : view) {
            hash += c;
            hash *= 17;
        }
        return hash;
    };

    for (auto const& segment : input_string | std::ranges::views::split(',')) {
        std::string_view segment_view(segment);
        int hash = calculate_hash(segment_view);

        auto label_end = std::find_if(segment_view.begin(), segment_view.end(), [](auto element){
            if (element == '=' || element == '-') {
                return true;
            }
            return false;
        });
        auto label = std::string_view(segment_view.begin(), label_end);

        int focal_length = charDigitToInt(segment_view.back()).value_or(0);
        Lens lens(label, focal_length);

        int label_hash = calculate_hash(label);
        auto& label_hashmap = part2_hashmap[label_hash];
        auto entry = std::find(label_hashmap.begin(), label_hashmap.end(), lens);

        if (*label_end == '=') {
            if (entry == label_hashmap.end()) {
                label_hashmap.push_back(lens);
            }
            else {
                *entry = lens;
            }
        }
        else if (*label_end == '-') {
            if (entry != label_hashmap.end()) {
                label_hashmap.erase(entry);
            }
        }

        part1_hashes.push_back(hash);
    }

    int i = 0;
    for (auto const& label_hashmap : part2_hashmap) {
        i++;
        int j = 1;
        for (auto const& lens : label_hashmap) {
            part2_result += i * j * lens.focal_length;
            j++;
        }
    }

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Hashes sum: " << std::reduce(part1_hashes.begin(), part1_hashes.end(), 0l) << std::endl;
    std::cout << "Task 2 - Total focusing power: " << part2_result << std::endl;
}
