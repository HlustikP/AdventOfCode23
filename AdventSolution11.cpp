#include <ranges>
#include <algorithm>

#include "utils.h"
#include "AdventSolution11.h"

constexpr char EMPTY_SPACE = '.';
constexpr char GALAXY_CHAR = '#';

struct TwoDPoint {
    TwoDPoint(int x, int y) : x(x), y(y) {}

    int x {};
    int y {};

    friend std::ostream& operator<<(std::ostream& os, const TwoDPoint& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

static int get_point_distance(const TwoDPoint& p1, const TwoDPoint& p2) {
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
}

static std::vector<int> get_lines_with_only_empty_space(const std::string& input_string, int line_size) {
    std::vector<int> lines_with_only_empty_space;

    int line_index = 0;
    for (const auto& str : std::views::split(input_string, NEWLINE_DELIMITER)) {
        if (str.size() > 0 && std::ranges::all_of(str, [](const auto& c) { return c == EMPTY_SPACE; })) {
            lines_with_only_empty_space.push_back(line_index);
        }
        line_index++;
    }

    return lines_with_only_empty_space;
}

static std::vector<int> get_col_with_only_empty_space(const std::string& input_string, int line_size) {
    std::vector<int> lines_with_only_empty_space;

    // account for the newline delimiter
    line_size++;

    for (auto col_index = 0; col_index < line_size - 1; col_index++) {
        for (auto i = col_index; i < input_string.size(); i += line_size) {
            if (input_string.at(i) != EMPTY_SPACE) {
                break;
            }

            // if we are at the last line, then we have only had empty space
            if (i > input_string.size() - line_size) {
                lines_with_only_empty_space.push_back(col_index);
            }
        }
    }

    return lines_with_only_empty_space;
}

static int get_num_of_empty_lines_between(TwoDPoint& p1, TwoDPoint& p2, const std::vector<int>& empty_lines) {
    const auto [x1, y1] = p1;
    const auto [x2, y2] = p2;

    if (y1 == y2) {
        return 0;
    }

    const auto min_y = std::min(y1, y2);
    const auto max_y = std::max(y1, y2);

    int num_of_empty_lines = 0;
    for (auto& empty_line : empty_lines) {
        if (empty_line > min_y && empty_line < max_y) {
            num_of_empty_lines++;
        }
    }

    return num_of_empty_lines;
}

static int get_num_of_empty_cols_between(TwoDPoint& p1, TwoDPoint& p2, const std::vector<int>& empty_cols) {
    const auto [x1, y1] = p1;
    const auto [x2, y2] = p2;

    if (x1 == x2) {
        return 0;
    }

    const auto min_x = std::min(x1, x2);
    const auto max_x = std::max(x1, x2);

    int num_of_empty_cols = 0;
    for (auto& empty_col : empty_cols) {
        if (empty_col > min_x && empty_col < max_x) {
            num_of_empty_cols++;
        }
    }

    return num_of_empty_cols;
}

void AdventSolution11::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input11.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();

    const auto line_size = input_string.find(NEWLINE_DELIMITER);
    const auto line_count = std::ranges::count(input_string, NEWLINE_DELIMITER);
    std::vector<TwoDPoint> points;

    int char_index = 0;
    for (auto itr = input_string.begin(); itr < input_string.end(); itr++) {
        if (*itr == NEWLINE_DELIMITER) {
            continue;
        }

        if (*itr == GALAXY_CHAR) {
            points.emplace_back(char_index % line_size, char_index / line_size);
        }

        char_index++;
    }

    const auto lines_with_only_empty_space = get_lines_with_only_empty_space(input_string, line_size);
    const auto cols_with_only_empty_space = get_col_with_only_empty_space(input_string, line_size);

    int64_t accumulated_point_distance = 0;
    for (auto i = 0; i < points.size(); i++) {
        for (auto j = i + 1; j < points.size(); j++) {
            accumulated_point_distance += get_point_distance(points[i], points[j]);
            accumulated_point_distance += get_num_of_empty_lines_between(points[i], points[j], lines_with_only_empty_space);
            accumulated_point_distance += get_num_of_empty_cols_between(points[i], points[j], cols_with_only_empty_space);
        }
    }

    int64_t accumulated_point_distance_part2 = 0;
    for (auto i = 0; i < points.size(); i++) {
        for (auto j = i + 1; j < points.size(); j++) {
            accumulated_point_distance_part2 += get_point_distance(points[i], points[j]);
            accumulated_point_distance_part2 += get_num_of_empty_lines_between(points[i], points[j], lines_with_only_empty_space) * 999999;
            accumulated_point_distance_part2 += get_num_of_empty_cols_between(points[i], points[j], cols_with_only_empty_space) * 999999;
        }
    }

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Accumulated Point Distance: " << accumulated_point_distance << std::endl;
    std::cout << "Task 2 - Accumulated Point Distance: " << accumulated_point_distance_part2 << std::endl;
}
