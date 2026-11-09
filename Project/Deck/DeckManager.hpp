//
// Created by Jet on 11/7/2026.
//
// DeckManager: manages the draw and discard pile. It is the only class that
// moves cards between the piles and the players.
//
// Deck size is set with rankSize and suitSize (rules: Contents):
//   minimum game: rankSize 10 (Ace to 10) x suitSize 4 + 2 Jokers = 42 cards
//   power cards:  rankSize 13 (adds Jack, Queen, King)          = 54 cards
//
#ifndef PROJECT_DECKMANAGER_HPP
#define PROJECT_DECKMANAGER_HPP

#include <iostream>
#include "deck.hpp"

class PlayHand;

class DeckManager {
public:
    static const int SUIT_SIZE = 4;
    static const int RANK_SIZE_MIN_GAME = 10; // Ace to 10
    static const int RANK_SIZE_POWER = 13;    // Ace to King
    static const int NUM_JOKERS = 2;

    //powerCards = false for the minimum game (42 cards)
    explicit DeckManager(bool powerCards = false);

    //Destructor (each Deck frees its own cards)
    ~DeckManager() = default;

    //Changes the deck that startNewRound() builds (custom decks)
    void setDeckSize(int rankSize, int suitSize, int numJokers);

    //rankSize * suitSize + numJokers
    [[nodiscard]] int getDeckSize() const;

    //Empties both piles, builds a new shuffled draw pile with genIndex() + genDeck(),
    //then flips the top card to start the discard pile. If that card is a Power
    //card it is placed back in the deck and another card is turned over (rules: Set-up).
    void startNewRound();

    //Shuffles the draw pile into a random order
    void shuffle();

    //Deals 4 cards to a player's hand
    void deal(PlayHand &hand);

    //Draws the top card from the active draw pile (returns + removes it).
    //Calls refillDrawPile() first if the draw pile is empty.
    Card drawFromPile();

    //Draws the top card from the discard pile (returns + removes it)
    Card drawFromDiscard();

    //Returns the top card of the discard pile without removing it
    [[nodiscard]] Card peekAtDiscard() const;

    [[nodiscard]] bool discardIsEmpty() const;

    //Places a card face up on the discard pile
    void discard(const Card &c);

    //Rules: when the draw pile runs out, the discard pile except its top card is
    //shuffled into a new draw pile; the top card stays face up as the discard pile
    void refillDrawPile();

    //Shows the top of the discard pile
    void printDiscard(std::ostream &outs) const;

private:
    Deck drawPile;    // the pile players draw from
    Deck discardPile; // the face-up pile of discarded cards
    int rankSize;
    int suitSize;
    int numJokers;
};

#endif //PROJECT_DECKMANAGER_HPP
