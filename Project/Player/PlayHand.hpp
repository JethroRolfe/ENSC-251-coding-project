//
// Created by Jet on 11/7/2026.
//
// PlayHand: a player's four face-down cards kept in fixed positions 1 to 4,
// plus 2 temp locations for cards that have been drawn but not placed yet
// (one normal draw, or the two cards of a Draw 2).
//
// Rules used here:
//  - A card from the discard pile MUST replace one of the player's cards.
//  - Draw 2: up to 2 cards are held at once; each can be swapped in or discarded.
//  - At the start of the round the player may reorder their cards once.
//
#ifndef PROJECT_PLAYHAND_HPP
#define PROJECT_PLAYHAND_HPP

#include <iostream>
#include "../Deck/Card/card.hpp"

//Where a drawn card came from (a card from the discard pile must be swapped in)
enum class DeckChoice : int {
    DrawPile = 1,
    DiscardPile = 2,
};

class PlayHand {
public:
    static const int HAND_SIZE = 4; // positions 1-4
    static const int TEMP_SIZE = 2; // temp 1 and temp 2

    //Constructor (empty hand, nothing known)
    PlayHand();

    //Destructor (no dynamic memory)
    ~PlayHand() = default;

    //Puts a dealt card at pos (1-4) and returns the card that was there
    Card setCard(int pos, const Card &c);

    //Adds a drawn card to the first free temp location; from = which pile it came from.
    //Returns the temp number used (1 or 2), or 0 if both temps are full.
    int addCard(const Card &c, DeckChoice from);

    //Swaps temp 1 or temp 2 into position pos (1-4). Returns the old card, which goes
    //to the discard pile. The new card at pos is now known to the player.
    Card replaceCard(int pos, int whichTemp);

    //Removes the card in temp 1 or temp 2 so it can be discarded.
    //Not allowed if it came from the discard pile (mustReplace).
    Card takeTemp(int whichTemp);

    [[nodiscard]] bool hasTemp(int whichTemp) const;

    //True if the temp card came from the discard pile and must be swapped in
    [[nodiscard]] bool mustReplace(int whichTemp) const;

    //Returns the card at pos (1-4) without changing it, for cout << *peekCard(pos)
    [[nodiscard]] const Card *peekCard(int pos) const;

    //Returns the card in temp 1 or temp 2, nullptr if empty
    [[nodiscard]] const Card *peekTemp(int whichTemp) const;

    //Reorders two of the player's cards (allowed once, at the initial peek)
    void swapPositions(int posA, int posB);

    //Checks if position is between 1 and 4
    [[nodiscard]] bool isValidPos(int pos) const;

    //Known cards: shown in easy mode, and used by bots
    [[nodiscard]] bool isKnown(int pos) const;

    void setKnown(int pos, bool isKnown);

    //Empties the hand and temps (cards are collected at the end of a round)
    void clear();

    //Prints the hand as [?] [?] [?] [?]; in easy mode the known cards are revealed
    void printHidden(std::ostream &outs, bool easyMode = false) const;

    //Prints all four cards at the end of the round
    void printRevealed(std::ostream &outs) const;

    //Returns the value of the hand: sum of rankValue() of the 4 cards
    [[nodiscard]] int handScore() const;

private:
    Card cards[HAND_SIZE + TEMP_SIZE];  // [0-3] = positions 1-4, [4],[5] = temp 1, temp 2
    bool tempUsed[TEMP_SIZE];           // true if the temp location holds a card
    DeckChoice tempFrom[TEMP_SIZE];     // which pile each temp card came from
    bool known[HAND_SIZE];              // cards the player has seen
};

#endif //PROJECT_PLAYHAND_HPP
