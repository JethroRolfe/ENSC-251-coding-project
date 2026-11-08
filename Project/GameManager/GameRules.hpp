//
// Created by Jet on 11/7/2026.
//
// GameRules: switch of the cards, with cases on King, Queen, Jack for the powers
// (group doc). Called by Player::ruleCheck.
// Power cards are a planned extension; the minimum viable game has none.
//
// Official power cards: Peek, Swap, Draw 2.
// PROPOSED (still undecided by the group): Jack = Peek, Queen = Swap, King = Draw 2.
//
#ifndef PROJECT_GAMERULES_HPP
#define PROJECT_GAMERULES_HPP

#include <iostream>
#include "../Deck/Card/card.hpp"

class Player;
class DeckManager;
class PlayHand;

class GameRules {
public:
    //Constructor (powerCardsOn = false for the minimum viable game)
    explicit GameRules(bool powerCardsOn = false);

    //Destructor (no dynamic memory)
    ~GameRules() = default;

    [[nodiscard]] bool powerCardsOn() const;

    //Card from the discard pile: it MUST replace one of the player's cards.
    //The replaced card is discarded face up.
    void useDiscardCard(const Card &card, Player &player, DeckManager &decks) const;

    //Card from the draw pile: switch on the card.
    //Number card: replace one of the player's cards, or discard it.
    //Jack = Peek, Queen = Swap, King = Draw 2: use its power, or discard it.
    void useDrawnCard(const Card &card, Player **players, int numPlayers,
                      int current, DeckManager &decks) const;

    //End of round: players replace all power cards by drawing from the draw pile.
    //If another power card is drawn, the player draws again.
    void replacePowerCards(PlayHand &hand, DeckManager &decks) const;

    //Explains a specific power card's rule (group doc: explainCard)
    void explainCard(const Card &card, std::ostream &outs) const;

    //Explains the player's available options (group doc: explainRules)
    void explainRules(std::ostream &outs) const;

private:
    bool usePowers;

    //Peek: look at any one of your own cards. Turn is over, Peek card is discarded.
    void peek(Player &player) const;

    //Swap: discard the Swap card; optionally switch one of your cards with any card
    //of another player, without looking at either card. Turn is over.
    void swap(Player **players, int numPlayers, int current) const;

    //Draw 2: draw the next card; use it (forfeit the second draw) OR discard it and
    //draw a second card, which may be used or discarded. Another Draw 2 starts the
    //sequence again (calls useDrawnCard again).
    void drawTwo(Player **players, int numPlayers, int current, DeckManager &decks) const;
};

#endif //PROJECT_GAMERULES_HPP
