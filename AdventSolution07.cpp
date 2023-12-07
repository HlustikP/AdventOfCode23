#include <ranges>
#include <algorithm>

#include "utils.h"
#include "AdventSolution07.h"

enum PokerHandValue {
    HighCard,
    OnePair,
    TwoPairs,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind
};

static bool is_part_1 = true;

constexpr std::array poker_cards_part_1 = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
constexpr std::array poker_cards_part_2 = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};

class PokerHand {
public:
    PokerHand(std::string cards, int bet) : cards_(cards), bet_(bet) {
        evaluateHand();
    }

    void reEvaluateHand() {
        // Jokers wont change this hand
        if (value_ == PokerHandValue::FiveOfAKind) {
            return;
        }

        // No jokers, no need to re-evaluate
        auto const joker_count = std::count(cards_.begin(), cards_.end(), 'J');
        if (joker_count == 0) {
            return;
        }
        
        if (value_ == PokerHandValue::FourOfAKind) {
            value_ = PokerHandValue::FiveOfAKind;
            return;
        }

        if (value_ == PokerHandValue::FullHouse) {
            value_ = PokerHandValue::FiveOfAKind;
            return;
        }

        if (value_ == PokerHandValue::ThreeOfAKind) {
            value_ = PokerHandValue::FourOfAKind;
            return;
        }

        if (value_ == PokerHandValue::TwoPairs) {
            value_ = joker_count == 1 ? PokerHandValue::FullHouse : PokerHandValue::FourOfAKind;
            return;
        }

        if (value_ == PokerHandValue::OnePair) {
            value_ = PokerHandValue::ThreeOfAKind;
            return;
        }

        value_ = PokerHandValue::OnePair;
    }

    int getBet() const {
        return bet_;
    }

    bool operator<(const PokerHand& other) const {
        if (value_ < other.value_) {
            return true;
        }
        if (value_ > other.value_) {
            return false;
        }

        // Find the first differing card
        auto differing_cards = std::mismatch(cards_.begin(), cards_.end(), other.cards_.begin(), other.cards_.end());

        if (differing_cards.first == cards_.end()) {
            return false;
        }

        // Get the value of the differing cards
        auto poker_cards = is_part_1 ? &poker_cards_part_1 : &poker_cards_part_2;
        const auto value_lhs = std::distance(poker_cards->begin(), std::find(poker_cards->begin(), poker_cards->end(), *differing_cards.first));
        const auto value_rhs = std::distance(poker_cards->begin(), std::find(poker_cards->begin(), poker_cards->end(), *differing_cards.second));

        return value_lhs < value_rhs;
    }

    bool operator>(const PokerHand& other) const {
        if (value_ > other.value_) {
            return true;
        }
        if (value_ < other.value_) {
            return false;
        }

        // Find the first differing card
        auto differing_cards = std::mismatch(cards_.begin(), cards_.end(), other.cards_.begin(), other.cards_.end());

        if (differing_cards.first == cards_.end()) {
            return false;
        }

        // Get the value of the differing cards
        auto poker_cards = is_part_1 ? &poker_cards_part_1 : &poker_cards_part_2;
        const auto value_lhs = std::distance(poker_cards->begin(), std::find(poker_cards->begin(), poker_cards->end(), *differing_cards.first));
        const auto value_rhs = std::distance(poker_cards->begin(), std::find(poker_cards->begin(), poker_cards->end(), *differing_cards.second));

        return value_lhs > value_rhs;
    }

    bool operator==(const PokerHand& other) const {
        return cards_ == other.cards_;
    }

    friend std::ostream& operator<<(std::ostream& os, const PokerHand& hand) {
        os << "Hand: " << hand.cards_ << " Value: " << hand.value_ << " Bet:" << hand.bet_;
        return os;
    }

private:
    void evaluateHand() {
        // Check how much of each card there is
        std::vector<int> card_counts(13, 0);
        for (const auto& card : cards_) {
            const auto card_value = std::distance(poker_cards_part_1.begin(), std::find(poker_cards_part_1.begin(), poker_cards_part_1.end(), card));
            card_counts[card_value] += 1;
        }

        std::sort(card_counts.begin(), card_counts.end(), [](auto lhs, auto rhs){
            return lhs > rhs;
        });

        if (card_counts[0] == 5) {
            value_ = PokerHandValue::FiveOfAKind;
            return;
        }

        if (card_counts[0] == 4) {
            value_ = PokerHandValue::FourOfAKind;
            return;
        }

        if (card_counts[0] == 3 && card_counts[1] == 2) {
            value_ = PokerHandValue::FullHouse;
            return;
        }

        if (card_counts[0] == 3) {
            value_ = PokerHandValue::ThreeOfAKind;
            return;
        }

        if (card_counts[0] == 2 && card_counts[1] == 2) {
            value_ = PokerHandValue::TwoPairs;
            return;
        }

        if (card_counts[0] == 2) {
            value_ = PokerHandValue::OnePair;
            return;
        }

        value_ = PokerHandValue::HighCard;
    }

    PokerHandValue value_ {};
    std::string cards_ {};
    int bet_ {};
};

void AdventSolution07::solve() {
    start_ = std::chrono::high_resolution_clock::now();

    const auto input = readFile("input07.txt");
    if (!input) {
        return;
    }

    const auto& input_string = input.value();
    const auto line_count = std::count(input_string.begin(), input_string.end(), NEWLINE_DELIMITER);

    std::vector<PokerHand> hands;
    hands.reserve(line_count);

    for (const auto& str : std::views::split(input.value(), NEWLINE_DELIMITER)) {
        auto line = std::string_view(str);
        auto const cards_string = std::string(line.substr(0, 5));
        auto itr = line.rbegin();
        int bet = 0;
        int current_digit = 0;

        while (*itr != ' ') {
            if (*itr == NEWLINE_DELIMITER) {
                ++itr;
                continue;
            }

            bet += charDigitToInt(*itr).value_or(0) * static_cast<int>(std::pow(10, current_digit));
            ++current_digit;

            ++itr;
        }
        
        PokerHand hand(cards_string, bet);
        bool inserted = false;
        for (auto& recorded_hand : hands) {
            if (hand > recorded_hand) {
                hands.insert(std::find(hands.begin(), hands.end(), recorded_hand), hand);
                inserted = true;
                break;
            }
        }
        // If the hand is the worst, just push it to the vector's back
        if (!inserted) {
            hands.push_back(hand);
        }
    }

    is_part_1 = false;
    std::vector<PokerHand> part_2_hands;
    part_2_hands.reserve(line_count);

    for (auto& hand : hands) {
        hand.reEvaluateHand();

        bool inserted = false;
        for (auto& recorded_hand : part_2_hands) {
            if (hand > recorded_hand) {
                part_2_hands.insert(std::find(part_2_hands.begin(), part_2_hands.end(), recorded_hand), hand);
                inserted = true;
                break;
            }
        }
        // If the hand is the worst, just push it to the vector's back
        if (!inserted) {
            part_2_hands.push_back(hand);
        }
    }

    auto sum = 0;
    auto current_pos = 1;
    for (auto itr = hands.rbegin(); itr < hands.rend(); itr++, current_pos++) {
        sum += itr->getBet() * current_pos;
    }

    auto sum_part_2 = 0;
    current_pos = 1;
    for (auto itr = part_2_hands.rbegin(); itr < part_2_hands.rend(); itr++, current_pos++) {
        sum_part_2 += itr->getBet() * current_pos;
    }

    end_ = std::chrono::high_resolution_clock::now();

    std::cout << "Task 1 - Total Winnings: " << sum << std::endl;
    std::cout << "Task 2 - Total Winnings with Jokers: " << sum_part_2 << std::endl;
}
