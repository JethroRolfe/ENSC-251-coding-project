//
// Created by jet on 9/23/26.
//
#include "card.hpp"
#include <string>

//enum to string Suit
const char *Card::to_string(const Suit s) {
    switch (s) {
        case Suit::Clubs: return "Clubs";
        case Suit::Diamonds: return "Diamonds";
        case Suit::Hearts: return "Hearts";
        case Suit::Spades: return "Spades";
        default: return "unknown";
    }
}

//enum to string Rank
const char *Card::to_string(const Rank r) {
    switch (r) {
        case Rank::Joker: return "Joker";
        case Rank::Ace: return "Ace";
        case Rank::Two: return "2";
        case Rank::Three: return "3";
        case Rank::Four: return "4";
        case Rank::Five: return "5";
        case Rank::Six: return "6";
        case Rank::Seven: return "7";
        case Rank::Eight: return "8";
        case Rank::Nine: return "9";
        case Rank::Ten: return "10";
        case Rank::Jack: return "Jack";
        case Rank::Queen: return "Queen";
        case Rank::King: return "King";
        default: return "unknown";
    }
}

//Default constructor, Ace of Clubs
Card::Card() : rank(Rank::Ace), suit(Suit::Clubs) {
}

Card::Card(const Rank r, const Suit s) : rank(r), suit(s) {
    (void) isValid();
}

//Card constructor from ints, with isValid check on rank and suit
Card::Card(const int r, const int s) : rank(static_cast<Rank>(r)), suit(static_cast<Suit>(s)) {
    (void) isValid();
}

//Checks if both Suit and Rank are valid
bool Card::isValid() const {
    const int r = static_cast<int>(rank);
    const int s = static_cast<int>(suit);
    if (r < static_cast<int>(Rank::Joker) || r > static_cast<int>(Rank::King) ||
        s < static_cast<int>(Suit::Clubs) || s > static_cast<int>(Suit::Spades)) {
        std::cerr << "ERROR: Invalid card parameters (Rank: " << r << ", Suit: " << s << ")\n";
        return false;
    }
    return true;
}

Rank Card::getRank() const { return rank; }

Suit Card::getSuit() const { return suit; }

//Point value in the game: rank + suit, Joker = 0, power cards = 0 (replaced before scoring)
int Card::rankValue() const {
    if (isJoker() || isFaceCard()) return 0;
    return static_cast<int>(rank) + static_cast<int>(suit);
}

//Checks if Card is a Face Card (Jack, Queen, King = Power Cards)
bool Card::isFaceCard() const {
    return rank >= Rank::Jack && rank <= Rank::King;
}

bool Card::isJoker() const { return rank == Rank::Joker; }

//overload of <,> and ==
bool Card::operator==(const Card &other) const {
    return rank == other.rank && suit == other.suit;
}

bool Card::operator>(const Card &other) const {
    if (rankValue() != other.rankValue()) return rankValue() > other.rankValue();
    return suit > other.suit;
}

bool Card::operator<(const Card &other) const {
    if (rankValue() != other.rankValue()) return rankValue() < other.rankValue();
    return suit < other.suit;
}

//Stream operators

//Reads a card in the format "[Rank] of [Suit]"
//if input !isValid Recall the operator
std::istream &operator>>(std::istream &ins, Card &c) {
    std::string rankText, ofText, suitText;
    if (!(ins >> rankText >> ofText >> suitText)) return ins;

    int newRank = -1;
    int newSuit = -1;

    for (int i = static_cast<int>(Rank::Joker); i <= static_cast<int>(Rank::King); i++) {
        if (rankText == Card::to_string(static_cast<Rank>(i))) newRank = i;
    }
    for (int i = static_cast<int>(Suit::Clubs); i <= static_cast<int>(Suit::Spades); i++) {
        if (suitText == Card::to_string(static_cast<Suit>(i))) newSuit = i;
    }

    if (newRank == -1 || newSuit == -1 || ofText != "of") {
        std::cout << "Invalid card, try again: ";
        return ins >> c;
    }

    c = Card(newRank, newSuit);
    return ins;
}

//Outputs [Rank] of [Suit] for a Card ("Joker" for a Joker)
std::ostream &operator<<(std::ostream &outs, const Card &c) {
    if (c.isJoker()) return outs << Card::to_string(c.rank);
    outs << Card::to_string(c.rank) << " of " << Card::to_string(c.suit);
    return outs;
}
