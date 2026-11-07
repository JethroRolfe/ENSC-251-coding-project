//
// Created by jet on 9/23/26.
//
#ifndef LAB2_CARD_HPP
#define LAB2_CARD_HPP
#define ACE_HIGH
#include <iostream>

//Ranks Ace,2,...,10,Jack,Queen,King
enum class Rank : int {
    Ace = 1,
    Two, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten,
    Jack = 11,
    Queen = 12,
    King = 13,
};

//Suits Clubs, Diamonds, Hearts, Spades
enum class Suit : int {
    Clubs = 0,
    Diamonds = 1,
    Hearts = 2,
    Spades = 3,
};

class card {
private:
    int rank;
    int suit;

    //Rank Value for AceHigh
    int rankValue() const;

    //enum to string
    static const char *to_string(Suit s);

    static const char *to_string(Rank r);

public:
    card();

    card(int r, int s);

    //Validation
    [[nodiscard]] bool isValid() const;

    //overload of <,> and ==
    bool operator==(const card &c2) const;

    bool operator>(const card &c2) const;

    bool operator<(const card &c2) const;

    //Stream operators
    friend std::ostream &operator<<(std::ostream &outs, const card &c);

    friend std::istream &operator>>(std::istream &ins, card &c);

    //Face card evaluation
    [[nodiscard]] bool isFaceCard() const;
};
#endif //LAB2_CARD_HPP
