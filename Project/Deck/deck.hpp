//
// Created by jet on 9/28/26.
//
// Deck: a pile of cards (same as Lab 2), stored in one singularLinkedList<Card>.
// The head of the list is the top of the pile.
// DeckManager uses two: the active draw pile and the discard pile.
//
// Custom decks (rules: Contents): a deck is rankSize ranks x suitSize suits,
// plus Jokers. randomVector() makes a shuffled array of ints 0 to size-1 and
// genDeck() turns each int into a card:
//     rank = index / suitSize + 1   (names from the Rank enum: Ace, 2..10, Jack, Queen, King)
//     suit = index % suitSize
//     index >= rankSize * suitSize  -> Joker
// Minimum game: rankSize = 10 (Ace to 10), suitSize = 4, 2 Jokers = 42 cards.
// With power cards: rankSize = 13 (adds Jack, Queen, King) = 54 cards.
//
#ifndef PROJECT_DECK_HPP
#define PROJECT_DECK_HPP

#include <iostream>
#include <vector>
#include "Card/card.hpp"
#include "Card/singularLinkedList.hpp"

class Deck {
public:
    //Default constructor (empty deck)
    Deck();

    //Deep copies a Deck with =
    Deck &operator=(const Deck &other);

    //Deep copies a Deck with copy constructor
    Deck(Deck const &other);

    //Destructor (cardList frees its own nodes)
    ~Deck() = default;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] int getNumCards() const;

    //Draws the top card (removes it from the deck)
    Card drawTopCard();

    //Adds Card to the top of the deck
    bool addCard(const Card &c);

    //Returns the top card without removing it (used for the discard pile)
    [[nodiscard]] Card peekTopCard() const;

    //Removes every card
    void clear();

    //Shuffles the cards already in the deck (used when the discard pile
    //becomes the new draw pile)
    void shuffle();

    //Prints the Deck
    void printDeck(std::ostream &outs) const;

    //Generates the deck from an array of ints made by randomVector().
    //size = rankSize * suitSize + numJokers. Clears the deck first.
    //rankSize 1-13, suitSize 1-4; returns false (deck left empty) if out of range.
    bool genDeck(int rankSize, int suitSize, int numJokers);

private:
    singularLinkedList<Card> cardList; // Linked list of Cards, head = top

    //Returns the numbers 0 to range-1 in a random order (Fisher-Yates shuffle)
    static std::vector<int> randomVector(int range);
};

#endif //PROJECT_DECK_HPP
