#include <ranges>
#include <functional>

#include "utils.h"
#include "AdventSolution16.h"

constexpr char EMPTY_CHAR = '.';

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

static bool will_hit_border(const std::string& map, int line_size, int next_position, const Direction direction) {
    return next_position < 0 || next_position >= map.size() || map[next_position] == NEWLINE_DELIMITER;
}

static int calculate_next_tile(int line_size, int current_position, const Direction direction) {
    switch (direction) {
        case Direction::UP:
            return current_position - line_size;
        case Direction::RIGHT:
            return current_position + 1;
        case Direction::DOWN:
            return current_position + line_size;
        case Direction::LEFT:
            return current_position - 1;
    }
}

void AdventSolution16::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile(input_);
    if (!input) {
        return;
    }

    const auto& input_string = input.value();
    const auto line_size = static_cast<int>(input_string.find(NEWLINE_DELIMITER)) + 1;
    const auto line_count = static_cast<int>(std::ranges::count(input_string, NEWLINE_DELIMITER));

    std::vector<char> energized_tiles(input_string.size(), 0);
    std::vector<char> visited_tiles(input_string.size(), 0);

    int energizing_highscore = 0;

    std::function<void(int, Direction)> move_beam;
    move_beam = [&move_beam , &input_string, &energized_tiles, &visited_tiles, line_size, line_count](int next_tile, Direction direction) {
        if (will_hit_border(input_string, line_size, next_tile, direction)) {
            return;
        }

        energized_tiles[next_tile] = 1;

        // If we already visited this tile in this direction, we can stop here
        if (visited_tiles[next_tile] & (1 << direction)) {
            return;
        }

        visited_tiles[next_tile] = visited_tiles[next_tile] | (1 << direction);

        if (input_string[next_tile] == EMPTY_CHAR) {
            next_tile = calculate_next_tile(line_size, next_tile, direction);
            return move_beam(next_tile, direction);
        }

        if (input_string[next_tile] == '/') {
            switch (direction) {
                case Direction::UP:
                    direction = Direction::RIGHT;
                    break;
                case Direction::RIGHT:
                    direction = Direction::UP;
                    break;
                case Direction::DOWN:
                    direction = Direction::LEFT;
                    break;
                case Direction::LEFT:
                    direction = Direction::DOWN;
                    break;
            }

            next_tile = calculate_next_tile(line_size, next_tile, direction);
            return move_beam(next_tile, direction);
        } else if (input_string[next_tile] == '\\') {
            switch (direction) {
                case Direction::UP:
                    direction = Direction::LEFT;
                    break;
                case Direction::RIGHT:
                    direction = Direction::DOWN;
                    break;
                case Direction::DOWN:
                    direction = Direction::RIGHT;
                    break;
                case Direction::LEFT:
                    direction = Direction::UP;
                    break;
            }

            next_tile = calculate_next_tile(line_size, next_tile, direction);
            return move_beam(next_tile, direction);
        }

        if (input_string[next_tile] == '|') {
            if (direction == Direction::UP || direction == Direction::DOWN) {
                next_tile = calculate_next_tile(line_size, next_tile, direction);
                return move_beam(next_tile, direction);
            }

            auto const original_tile = next_tile;
            next_tile = calculate_next_tile(line_size, next_tile, Direction::UP);
            move_beam(next_tile, Direction::UP);
            next_tile = calculate_next_tile(line_size, original_tile, Direction::DOWN);
            return move_beam(next_tile, Direction::DOWN);
        }

        if (input_string[next_tile] == '-') {
            if (direction == Direction::LEFT || direction == Direction::RIGHT) {
                next_tile = calculate_next_tile(line_size, next_tile, direction);
                return move_beam(next_tile, direction);
            }

            auto const original_tile = next_tile;
            next_tile = calculate_next_tile(line_size, next_tile, Direction::LEFT);
            move_beam(next_tile, Direction::LEFT);
            next_tile = calculate_next_tile(line_size, original_tile, Direction::RIGHT);
            return move_beam(next_tile, Direction::RIGHT);
        }
    };

    move_beam(0, Direction::RIGHT);
    const auto energized_count_part1 = static_cast<int>(std::ranges::count(energized_tiles, 1));

    for (int i = 0; i < line_size - 1; ++i) {
        std::ranges::fill(energized_tiles, 0);
        std::ranges::fill(visited_tiles, 0);

        move_beam(i, Direction::DOWN);
        auto energized_count = static_cast<int>(std::ranges::count(energized_tiles, 1));
        energizing_highscore = std::max(energizing_highscore, energized_count);

        std::ranges::fill(energized_tiles, 0);
        std::ranges::fill(visited_tiles, 0);

        move_beam(i + line_size * (line_count - 1), Direction::UP);
        energized_count = static_cast<int>(std::ranges::count(energized_tiles, 1));
        energizing_highscore = std::max(energizing_highscore, energized_count);
    }

    for (int i = 0; i < line_count - 1; ++i) {
        std::ranges::fill(energized_tiles, 0);
        std::ranges::fill(visited_tiles, 0);

        move_beam(i * line_size, Direction::RIGHT);
        auto energized_count = static_cast<int>(std::ranges::count(energized_tiles, 1));
        energizing_highscore = std::max(energizing_highscore, energized_count);

        std::ranges::fill(energized_tiles, 0);
        std::ranges::fill(visited_tiles, 0);

        move_beam((i + 1) * line_size - 1, Direction::LEFT);
        energized_count = static_cast<int>(std::ranges::count(energized_tiles, 1));
        energizing_highscore = std::max(energizing_highscore, energized_count);
    }

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Number of energized fields: " << energized_count_part1 << std::endl;
    std::cout << "Task 2 - Highscore for energizing: " << energizing_highscore << std::endl;
}
