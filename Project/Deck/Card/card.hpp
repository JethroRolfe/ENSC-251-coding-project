//
// Created by jet on 9/23/26.
//
// Card: one playing card (same as Lab 1).
// Group doc: the game uses Ace to 10 + 2 Jokers (minimum viable game),
// and King, Queen, Jack are the power cards (planned extension).
//
// Group decision (11/7): Joker = 0, number cards are worth their value
//   (Ace = 1, 2-10 = face value). Power cards have no point value.
// PROPOSED (still undecided): Jack = Peek, Queen = Swap, King = Draw 2.
// Standard deck + 2 Jokers = 54 cards, same count as the official game.
//
#ifndef PROJECT_CARD_HPP
#define PROJECT_CARD_HPP
#define ACE_HIGH
#include <iostream>

//Ranks Joker,Ace,2,...,10,Jack,Queen,King
enum class Rank : int {
    Joker = 0, // group doc: "Ace to 10 + 2 jokers"
    Ace = 1,
    Two, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten,
    Jack = 11,  // Peek   (proposed)
    Queen = 12, // Swap   (proposed)
    King = 13,  // Draw 2 (proposed)
};

//Suits Clubs, Diamonds, Hearts, Spades
enum class Suit : int {
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3,
};

class Card {
private:
    int rank;
    int suit;

    //Rank Value for AceHigh
    int rankValue() const;

    //enum to string
    static const char *to_string(Suit s);

    static const char *to_string(Rank r);

public:
    Card();

    Card(int r, int s);

    //Destructor (no dynamic memory)
    ~Card() = default;

    //Validation
    [[nodiscard]] bool isValid() const;

    //Getter, used by GameRules to switch on King/Queen/Jack
    [[nodiscard]] Rank getRank() const;

    //Point value of the card, used by Player::scoreCheck.
    //Joker = 0, Ace = 1, 2-10 = face value (group decision).
    //Power cards have no point value (official rules), returns 0.
    [[nodiscard]] int getPoints() const;

    //overload of <,> and ==
    bool operator==(const Card &c2) const;

    bool operator>(const Card &c2) const;

    bool operator<(const Card &c2) const;

    //Stream operators
    friend std::ostream &operator<<(std::ostream &outs, const Card &c);

    friend std::istream &operator>>(std::istream &ins, Card &c);

    //Face card evaluation (King, Queen, Jack = power cards)
    [[nodiscard]] bool isFaceCard() const;
};
#endif //PROJECT_CARD_HPP
