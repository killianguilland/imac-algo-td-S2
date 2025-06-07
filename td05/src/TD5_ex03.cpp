#include <string>
#include <iostream>
#include <vector>

enum class CardKind {
    Heart,
    Diamond,
    Club,
    Spade,
};

enum class CardValue {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};

struct Card {
    CardKind kind;
    CardValue value;

    bool operator==(const Card& other) const {
        return kind == other.kind && value == other.value;
    }

    std::size_t hash() const {
        // Il y a 13 valeurs possibles pour chaque couleur (kind)
        // On peut donc coder chaque carte par : 13 * kind + value
        return static_cast<std::size_t>(static_cast<int>(kind)) * 13 + static_cast<int>(value);
    }

    std::string get_name() const {
        std::string name {};

        unsigned int card_value {(static_cast<unsigned int>(value)+2) % 14};

        if (card_value < 10) {
            name += '0' + std::to_string(card_value);
        }else if (card_value == 10) {
            name += "10";
        }else if (card_value == 11) {
            name += 'J';
        }else if (card_value == 12) {
            name += 'Q';
        }else if (card_value == 13) {
            name += 'K';
        }

        name += " of ";

        if (kind == CardKind::Heart) {
            name += "Heart";
        }else if (kind == CardKind::Diamond) {
            name += "Diamond";
        }else if (kind == CardKind::Club) {
            name += "Club";
        }else if (kind == CardKind::Spade) {
            name += "Spade";
        }
        return name;
    }
};

namespace std {
    template<>
    struct hash<Card> {
        size_t operator()(Card const& card) const {
            return card.hash();
        }
    };
}

std::vector<Card> get_cards(size_t const size) {
    std::vector<Card> cards {};
    cards.reserve(size);
    for (size_t i {0}; i < size; ++i) {
        cards.push_back({static_cast<CardKind>(rand() % 4), static_cast<CardValue>(rand() % 13)});
    }
    return cards;
}

int main() {
    #include <unordered_map>

    auto cards = get_cards(100);
    std::unordered_map<Card, int> card_counts;

    for (const auto& card : cards) {
        ++card_counts[card];
    }

    for (const auto& pair : card_counts) {
        std::cout << pair.first.get_name() << ": " << pair.second << std::endl;
    }

    return 0;
}
