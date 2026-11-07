//
// Created by jet on 9/23/26.
//
#include  "card.hpp"
#include <string>

//enum to string Suit
const char *card::to_string(const Suit s) {
    switch (s) {
        case Suit::Clubs: return "Clubs";
        case Suit::Diamonds: return "Diamonds";
        case Suit::Hearts: return "Hearts";
        case Suit::Spades: return "Spades";
        default: return "unknown";
    }
}

//enum to string Rank
const char *card::to_string(const Rank r) {
    switch (r) {
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


//Default constructor, Rank: Ace, Suit: Spades
card::card() : rank(static_cast<int>(Rank::Ace)), suit(static_cast<int>(Suit::Spades)) {
}

//Card constructor, with isValid check on rank and suit
card::card(const int r, const int s) : rank(r), suit(s) {
    (void) isValid();
}

//Checks if Card is a Face Card
bool card::isFaceCard() const {
    return (rank >= 11 && rank <= 13);
}

//Checks if both Suit and Rank is valid
bool card::isValid() const {
    if (rank < 1 || rank > 13 || suit < 0 || suit > 3) {
        std::cerr << "ERROR: Invalid card parameters (Rank: " << rank << ", Suit: " << suit << ")\n";
        return false;
    }
    return true;
}

//Rank Value for AceHigh
int card::rankValue() const {
#ifdef ACE_HIGH
    if (rank == (static_cast<int>(Rank::Ace))) return 14;
#endif
    return rank;
}

//overload of <,> and ==
bool card::operator==(const card &other) const {
    return rank == other.rank && suit == other.suit;
}

bool card::operator>(const card &other) const {
    if (rankValue() != other.rankValue()) {
        return rankValue() > other.rankValue();
    }
    return suit > other.suit;
}

bool card::operator<(const card &other) const {
    if (rankValue() != other.rankValue()) {
        return rankValue() < other.rankValue();
    }
    return suit < other.suit;
}

//Stream operators

//Reads a card in the format "[Rank] of [Suit]"
//if input !isValid Recall the operator
std::istream &operator>>(std::istream &ins, card &c) {
    std::string rankText, ofText, suitText;
    if (!(ins >> rankText >> ofText >> suitText)) return ins;

    int newRank = -1;
    int newSuit = -1;

    for (int i = 1; i <= 13; i++) {
        if (rankText == card::to_string(static_cast<Rank>(i))) {
            newRank = i;
        }
    }

    for (int i = 0; i <= 3; i++) {
        if (suitText == card::to_string(static_cast<Suit>(i))) {
            newSuit = i;
        }
    }


    if (newRank == -1 || newSuit == -1 || ofText != "of") {
        std::cout << "Invalid card, try again: ";
        return ins >> c;
    }

    c = card(newRank, newSuit);
    return ins;
}

//Outputs [Rank] of [Suit] for a Card
std::ostream &operator<<(std::ostream &outs, const card &c) {
    outs << card::to_string(static_cast<Rank>(c.rank)) << " of "
            << card::to_string(static_cast<Suit>(c.suit));
    return outs;
}
