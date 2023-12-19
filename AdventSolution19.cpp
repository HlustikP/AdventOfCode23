#include <ranges>
#include <map>
#include <functional>

#include "utils.h"
#include "AdventSolution19.h"

struct MachinePart {
    int x {};
    int m {};
    int a {};
    int s {};
};

struct MachinePartCheck {
    char part {};
    bool greater_than {};
    int value {};
    std::string_view result {};
};

int* get_machine_part_member(MachinePart& part, char c) {
    switch (c) {
        case 'x':
            return &part.x;
        case 'm':
            return &part.m;
        case 'a':
            return &part.a;
        case 's':
            return &part.s;
        default:
            return nullptr;
    }
}

class Workflow {
public:
    Workflow() = default;
    Workflow(std::string_view name) : name_(std::move(name)) {}

    void add_check(MachinePartCheck&& check) {
        checks_.emplace_back(std::move(check));
    }

    const std::string_view get_name() const {
        return name_;
    }

    const std::vector<MachinePartCheck>& get_checks() const {
        return checks_;
    }
private:
    std::string_view name_;
    std::vector<MachinePartCheck> checks_;
};

void AdventSolution19::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile(input_);
    if (!input) {
        return;
    }

    const auto& input_string = input.value();
    std::vector<MachinePart> machine_parts;
    std::map<std::string_view, Workflow> workflows;
    std::vector<MachinePart*> rejected_parts;
    std::vector<MachinePart*> accepted_parts;

    for (const auto& str : input_string | std::ranges::views::split(NEWLINE_DELIMITER)) {
        auto line = std::string_view(str);

        auto open_bracket_ptr = std::ranges::find(line, '{');
        if (open_bracket_ptr == line.end()) {
            continue;
        }

        if (open_bracket_ptr == line.begin()) {
            auto nums = get_numbers_from_string(line);
            if (nums.size() != 4) {
                std::cerr << "Invalid machine part, got " << nums.size() << " numbers" << std::endl;
                continue;
            }

            machine_parts.emplace_back(nums[3], nums[2], nums[1], nums[0]);
            continue;
        }

        auto name = std::string_view(line.begin(), open_bracket_ptr);
        Workflow workflow(name);
        std::string_view checks_str(open_bracket_ptr + 1, line.end() - 1);

        for (const auto& inner_str : checks_str | std::ranges::views::split(',')) {
            auto check_str = std::string_view(inner_str);

            auto colon_ptr = std::ranges::find(check_str, ':');
            if (colon_ptr == check_str.end()) {
                workflow.add_check({ 0, false, 0, check_str });
                continue;
            }

            auto itr = check_str.begin();
            auto part = *itr;
            bool greater_than = *(++itr) == '>';
            auto value = std::stoi(std::string(++itr, colon_ptr));
            auto result = std::string_view(colon_ptr + 1, check_str.end());

            workflow.add_check({ part, greater_than, value, result });
        }
        workflows.emplace(name, std::move(workflow));
    }

    auto handle_result = [&accepted_parts, &rejected_parts, &workflows](MachinePart& part, std::string_view result)
        -> std::optional<Workflow*> {
        if (result == "A") {
            accepted_parts.push_back(&part);
            return std::nullopt;
        }
        else if (result == "R") {
            rejected_parts.push_back(&part);
            return std::nullopt;
        }
        else {
            return &(workflows[result]);
        }
    };

    auto* workflow = &(workflows["in"]);
    for (auto& part : machine_parts) {
        bool workflow_done = false;
        while (true) {
            auto& checks = workflow->get_checks();
            for (auto& check : checks) {
                if (check.part == 0) {
                    auto result = handle_result(part, check.result);
                    if (!result.has_value()) {
                        workflow_done = true;
                        break;
                    }
                    workflow = result.value();
                    break;
                }

                auto* part_member = get_machine_part_member(part, check.part);
                if (part_member == nullptr) {
                    std::cerr << "Invalid part member " << static_cast<int>(check.part) << std::endl;
                    workflow_done = true;
                    break;
                }

                if (check.greater_than) {
                    if (*part_member > check.value) {
                        auto result = handle_result(part, check.result);
                        if (!result.has_value()) {
                            workflow_done = true;
                            break;
                        }
                        workflow = result.value();
                        break;
                    }
                } else {
                    if (*part_member < check.value) {
                        auto result = handle_result(part, check.result);
                        if (!result.has_value()) {
                            workflow_done = true;
                            break;
                        }
                        workflow = result.value();
                        break;
                    }
                }
            }

            if (workflow_done) {
                workflow = &(workflows["in"]);
                break;
            }
        }
    }

    int64_t part1_sum = 0;
    for (auto* part : accepted_parts) {
        part1_sum += part->x;
        part1_sum += part->m;
        part1_sum += part->a;
        part1_sum += part->s;
    }

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Sum of all accepted parts' properties: " << part1_sum << std::endl;
    std::cout << "Task 2 - WIP" << std::endl;
}
