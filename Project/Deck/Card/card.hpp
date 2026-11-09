//
// Created by jet on 9/23/26.
//
// Card: one playing card (same as Lab 1).
//
// Rules (Contents): Joker = 0, Ace = 1, 2-10 = face value.
//   Card value = Rank + Suit (Clubs 0, Diamonds 1, Hearts 2, Spades 3),
//   to avoid ties at the end of the game. Jokers are always 0.
// Power cards (planned extension): Jack = Peek, Queen = Swap, King = Draw 2.
//   They have no point value and are replaced at the end of the round.
//
// The Rank enum controls the card names (Ace, Jack, Queen, King) used by
// Deck::genDeck when it builds a custom deck from rankSize and suitSize.
//
#ifndef PROJECT_CARD_HPP
#define PROJECT_CARD_HPP
#include <iostream>

//Ranks Joker, Ace, 2, ..., 10, Jack, Queen, King
enum class Rank : int {
    Joker = 0,
    Ace = 1,
    Two, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten,
    Jack = 11,  // Peek
    Queen = 12, // Swap
    King = 13,  // Draw 2
};

//Suits Clubs, Diamonds, Hearts, Spades (also their point value)
enum class Suit : int {
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3,
};

class Card {
private:
    Rank rank;
    Suit suit;

    //enum to string
    static const char *to_string(Suit s);

    static const char *to_string(Rank r);

public:
    //Default constructor: Ace of Clubs
    Card();

    Card(Rank r, Suit s);

    //Used when reading or generating cards from ints
    Card(int r, int s);

    //Destructor (no dynamic memory)
    ~Card() = default;

    //Checks if ranks are valid on construction
    [[nodiscard]] bool isValid() const;

    //Getters, used by GameRules to switch on King/Queen/Jack
    [[nodiscard]] Rank getRank() const;

    [[nodiscard]] Suit getSuit() const;

    //Returns the point value of a Card in the game: rank + suit (rules).
    //Joker = 0. Power cards (Jack, Queen, King) return 0; they are replaced
    //before scoring at the end of the round.
    [[nodiscard]] int rankValue() const;

    //Returns true if it is a Face Card (Jack, Queen, King) = Power Card; used by GameRules
    [[nodiscard]] bool isFaceCard() const;

    [[nodiscard]] bool isJoker() const;

    //Compare cards by point value, then suit
    bool operator==(const Card &c2) const;

    bool operator>(const Card &c2) const;

    bool operator<(const Card &c2) const;

    //Print/read as "[Rank] of [Suit]" (a Joker prints as "Joker")
    friend std::ostream &operator<<(std::ostream &outs, const Card &c);

    friend std::istream &operator>>(std::istream &ins, Card &c);
};
#endif //PROJECT_CARD_HPP
