//
// Created by Jet on 11/7/2026.
//
// PlayHand: the four cards a player keeps face down in a line (official rules).
// Stored in a singularLinkedList<Card> (group doc: "the linked list of their cards").
// Positions are 0-3, left to right. The outer cards are positions 0 and 3.
//
#ifndef PROJECT_PLAYHAND_HPP
#define PROJECT_PLAYHAND_HPP

#include <iostream>
#include "../Deck/Card/card.hpp"
#include "../Deck/Card/singularLinkedList.hpp"

class PlayHand {
public:
    static const int HAND_SIZE = 4; // dealer deals four cards to each player

    //Constructor (empty hand)
    PlayHand();

    //Destructor (cardList frees its own nodes)
    ~PlayHand() = default;

    //No copying (same as singularLinkedList)
    PlayHand(const PlayHand &) = delete;

    PlayHand &operator=(const PlayHand &) = delete;

    //Adds a dealt card to the end of the line
    void addCard(const Card &c);

    //Puts newCard at pos and returns the old card (to discard or swap)
    Card replaceCard(int pos, const Card &newCard);

    //Returns the card at pos without changing it (used for peeking)
    [[nodiscard]] Card getCard(int pos) const;

    //Removes all cards (cards are collected at the end of a round)
    void clear();

    //True if pos is between 0 and HAND_SIZE - 1
    [[nodiscard]] bool isValidPosition(int pos) const;

    //Shows the cards face down
    void displayHidden(std::ostream &outs) const;

    //Shows the cards face up (players turn over their cards at the end of the round)
    void displayRevealed(std::ostream &outs) const;

private:
    singularLinkedList<Card> cardList;
};

#endif //PROJECT_PLAYHAND_HPP
