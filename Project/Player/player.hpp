//
// Created by Jet on 11/2/2026.
//
// Player: uses one object of GameRules.
// Gets a card from the game manager and calls the game rules (group doc).
// Member functions from the group doc: RuleCheck, ScoreCheck, IO functions.
//
// The IO (decision) functions are virtual so Bot can inherit Player and
// answer them with its own list of rules instead of asking a person
// (group decision 11/7: "Bot should inherit player").
//
#ifndef PROJECT_PLAYER_HPP
#define PROJECT_PLAYER_HPP

#include <string>
#include "PlayHand.hpp"
#include "../GameManager/GameRules.hpp"

class DeckManager;

class Player {
public:
    //Default constructor
    Player();

    //Constructor with the player's name
    explicit Player(const std::string &name);

    //Virtual destructor so a Bot is deleted correctly through a Player pointer
    virtual ~Player() = default;

    //No copying (PlayHand cannot be copied)
    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

    //Getters / setters
    [[nodiscard]] std::string getName() const;

    void setName(const std::string &newName);

    PlayHand &getHand();

    [[nodiscard]] const PlayHand &getHand() const;

    [[nodiscard]] int getTotalScore() const;

    //Scorekeeper records each player's score at the end of each round
    void addToScore(int points);

    //True once the player's total reaches the score limit (they are out of the game)
    [[nodiscard]] bool isOut(int scoreLimit) const;

    //Reads the card the player got and runs the GameRules on it (group doc: RuleCheck).
    //fromDiscard = true: the card MUST replace one of the player's cards.
    //fromDiscard = false: the card may replace a card, use its power, or be discarded.
    void ruleCheck(const Card &card, bool fromDiscard, DeckManager &decks,
                   Player **players, int numPlayers);

    //Adds the point values of the four cards = score for the round (group doc: ScoreCheck)
    [[nodiscard]] int scoreCheck() const;

    // ---- IO functions (group doc). Bot overrides these. ----

    //Shows the top discard and asks:
    //1 = take the top card of the discard pile, 2 = draw from the draw pile
    [[nodiscard]] virtual int chooseDrawSource(const Card &topDiscard) const;

    //Asks the player to choose one of their four cards; returns position 0-3
    [[nodiscard]] virtual int chooseCardPosition(const std::string &prompt) const;

    //Asks a yes/no question (replace or discard, use a power, knock to end the round)
    [[nodiscard]] virtual bool askYesNo(const std::string &question) const;

    //Called whenever the player sees one of their own cards (outer cards, Peek,
    //replacing). Does nothing for a person (they remember it themselves);
    //Bot overrides it to store the card in its memory.
    virtual void remember(int pos, const Card &card);

private:
    std::string name;
    PlayHand hand;
    GameRules rules;
    int totalScore;
};

#endif //PROJECT_PLAYER_HPP
