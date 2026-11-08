//
// Created by Jet on 11/7/2026.
//
// DeckManager: uses 2 Deck objects, the draw pile and the discard pile.
// Manages the deck (only one deck object) and hands cards to the players.
//
#ifndef PROJECT_DECKMANAGER_HPP
#define PROJECT_DECKMANAGER_HPP

#include <iostream>
#include "deck.hpp"

class DeckManager {
private:
    Deck drawPile;    // face down in the middle of the table
    Deck discardPile; // face up

public:
    //Constructor (both piles empty)
    DeckManager();

    //Destructor (each Deck frees its own cards)
    ~DeckManager() = default;

    //Set-up (official rules): collects all cards, generates and shuffles the deck.
    //includePowerCards = false for the minimum viable game.
    void newRound(bool includePowerCards);

    //Set-up (official rules): the player to the left of the dealer cuts the cards
    void cut(int position);

    //Set-up (official rules): turns over the top card of the draw pile to start
    //the discard pile. If it is a power card, it goes back in the deck and
    //another card is turned over.
    void startDiscardPile();

    //Hands the top card of the draw pile to a player.
    //When the draw pile is used up, the discard pile is shuffled
    //and turned over for a new draw pile (official rules).
    Card drawFromDrawPile();

    //Hands the top card of the discard pile to a player
    Card drawFromDiscardPile();

    //Puts a card face up on the discard pile
    void discard(const Card &c);

    //Top card of the discard pile, without taking it
    [[nodiscard]] Card peekDiscard() const;

    [[nodiscard]] bool discardIsEmpty() const;

    //Shows the discard pile (group doc: displayDiscardPile)
    void displayDiscardPile(std::ostream &outs) const;
};

#endif //PROJECT_DECKMANAGER_HPP
