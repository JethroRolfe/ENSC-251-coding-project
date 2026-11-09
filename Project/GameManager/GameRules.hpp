//
// Created by Jet on 11/7/2026.
//
// GameRules: applies the Rat-a-Tat Cat rules to each turn. Owned and used by
// GameManager (not Player), because Swap needs access to two players' hands.
// It stores no game state; drawn cards are held in PlayHand's temp locations.
//
// Power cards are a planned extension; the minimum game has none.
//   Jack = Peek, Queen = Swap, King = Draw 2.
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
    //powerCardsOn = false for the minimum game
    explicit GameRules(bool powerCardsOn = false);

    //Destructor (no dynamic memory)
    ~GameRules() = default;

    [[nodiscard]] bool powerCardsOn() const;

    //Draws one card from the discard pile. It MUST replace one of the player's
    //cards; the replaced card is discarded face up. A Power card can be taken
    //from the discard pile but has no power.
    void drawFromDiscard(Player &player, DeckManager &decks) const;

    //Draws one card from the draw pile: the player replaces a card or discards it.
    //A Power card goes to whatPowerCard().
    void drawFromDraw(Player **players, int numPlayers, int current, DeckManager &decks) const;

    //Switch on the face cards: Jack = Peek, Queen = Swap, King = Draw 2.
    //Default: a normal card, which is replaced or discarded.
    void whatPowerCard(const Card &card, Player **players, int numPlayers, int current,
                       DeckManager &decks) const;

    //End of round: replaces power cards with the top card of the draw pile.
    //If another Power card is drawn, it goes to the discard pile and the player draws again.
    void replacePowerCards(PlayHand &hand, DeckManager &decks) const;

    //Replaces the player's power cards, then returns the hand's value (PlayHand::handScore)
    int scoreHand(Player &player, DeckManager &decks) const;

    //Explains a specific power card's rule
    void explainCard(const Card &card, std::ostream &outs) const;

    //Explains the player's available options
    void explainRules(std::ostream &outs) const;

private:
    bool usePowers;

    //Peek: look at any one of your own cards. Everyone sees the peek (rules).
    //Turn is over, the Peek card is discarded.
    void peek(Player &player) const;

    //Swap: the Swap card is discarded; optionally switch one of your cards with any
    //card of another player without looking. Both positions become unknown.
    //Order of questions: chooseOpponent (-1 = skip), choosePosition(Ask::SwapOwnPos),
    //choosePosition(Ask::SwapOpponentPos).
    void swap(Player **players, int numPlayers, int current) const;

    //Draw 2: draw 2 cards, each from the discard pile (must be swapped in) or the
    //draw pile, and hold them in the 2 temp locations. Then swap both, discard both,
    //or swap one and discard the other.
    //Another Draw 2: the cards already held must be swapped or discarded first,
    //then the sequence starts again. Peek or Swap: used as one of the 2 draws.
    void drawTwo(Player **players, int numPlayers, int current, DeckManager &decks) const;

    //Asks the player to swap in or discard every card held in the temps
    void placeTempCards(Player &player, DeckManager &decks) const;
};

#endif //PROJECT_GAMERULES_HPP
