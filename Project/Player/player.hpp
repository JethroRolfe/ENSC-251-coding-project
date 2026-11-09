//
// Created by Jet on 11/2/2026.
//
// Player: one player in the game. Asks the person for their choices (cin).
// The input functions are virtual so Bot can inherit Player and answer them
// with its own rules instead of asking a person.
//
// Rules used here:
//  - Knock tracking: knocking on your first turn of a round is allowed, but each
//    consecutive first-turn knock adds n to your score (n = number of consecutive
//    first-turn knocks; the first one is free). The count resets when the player
//    plays a round without knocking on their first turn.
//  - A player is out once their total reaches the score limit (GameManager::scoreLimit).
//
#ifndef PROJECT_PLAYER_HPP
#define PROJECT_PLAYER_HPP

#include <string>
#include "PlayHand.hpp"

//Why a position or a yes/no answer is being asked for. Lets Bot answer
//without reading the prompt text.
enum class Ask : int {
    PeekPos,         // Peek: which of your cards to look at
    SwapOwnPos,      // Swap: which of your cards to give away
    SwapOpponentPos, // Swap: which of the opponent's cards to take
    Reorder,         // initial peek: do you want to reorder your cards?
    ReorderFrom,     // initial peek: first position to swap
    ReorderTo,       // initial peek: second position to swap
    ShuffleRequest,  // first player: request a shuffle before any card is drawn?
};

class Player {
public:
    //Default constructor
    Player();

    //Constructor with the player's name
    explicit Player(const std::string &name);

    //Virtual destructor so a Bot is deleted correctly through a Player pointer
    virtual ~Player() = default;

    //Getters / setters
    [[nodiscard]] std::string getName() const;

    void setName(const std::string &newName);

    PlayHand &getHand();

    [[nodiscard]] const PlayHand &getHand() const;

    [[nodiscard]] int getTotalScore() const;

    [[nodiscard]] bool getIsOut() const;

    [[nodiscard]] virtual bool isBot() const;

    // ---- Input functions (cin). Bot overrides these. ----

    //Asks the player to draw from the draw pile or the discard pile
    [[nodiscard]] virtual DeckChoice whichDeck(const Card &topDiscard);

    //Asks which position (1-4) to swap the drawn card into, or 0 to discard it.
    //mustReplace = true (card from the discard pile): 0 is not allowed.
    [[nodiscard]] virtual int swapCardPos(const Card &drawn, bool mustReplace);

    //Draw 2: asks which held card to place next, temp 1 or temp 2
    [[nodiscard]] virtual int swapCardWith();

    //Asks for one of the player's positions 1-4 (Peek, Swap, reordering)
    [[nodiscard]] virtual int choosePosition(Ask why, const std::string &prompt);

    //Swap: asks which other player to swap with; returns their index,
    //or -1 to skip the swap (swapping is optional)
    [[nodiscard]] virtual int chooseOpponent(Player **players, int numPlayers, int self);

    //Yes/no questions: shuffle request, reorder at the peek
    [[nodiscard]] virtual bool askYesNo(Ask why, const std::string &question);

    //Asks if the player knocks (ends the round) at the end of their turn
    [[nodiscard]] virtual bool knock();

    // ---- Scoring ----

    //Adds the end of round score to the total score and keeps the worst round
    void addScore(int roundScore);

    //Knock tracking (rules): call once per round. Returns the penalty to add.
    int recordFirstTurnKnock(bool knockedOnFirstTurn);

    //Sets isOut when totalScore reaches scoreLimit
    void updateIsOut(int scoreLimit);

    //End screen stats
    [[nodiscard]] int getWorstRound() const;

protected:
    //Reads an int from cin between min and max, asking again on invalid input
    static int readInt(int min, int max);

private:
    std::string name;      // name of player
    PlayHand hand;         // the player's hand
    int totalScore;        // total score across rounds
    bool isOut;            // true once totalScore reaches the score limit
    int firstTurnKnocks;   // consecutive rounds the player knocked on their first turn
    int worstRound;        // highest single-round score (end screen)
};

#endif //PROJECT_PLAYER_HPP
