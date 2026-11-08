//
// Bot: a computer-controlled player (planned extension).
// Inherits Player and answers the IO functions with its own list of rules
// instead of asking a person (group decision 11/7).
//
// TODO (group): decide the bot's list of rules, e.g. when to take the
// discard, when to replace a card, when to use a power, when to knock.
//
#ifndef PROJECT_BOT_HPP
#define PROJECT_BOT_HPP

#include "player.hpp"

class Bot : public Player {
public:
    //Constructor with the bot's name
    explicit Bot(const std::string &name);

    //Destructor (no dynamic memory)
    ~Bot() override = default;

    //Picks the discard pile or the draw pile using the bot's rules
    [[nodiscard]] int chooseDrawSource(const Card &topDiscard) const override;

    //Picks which of its cards to use using the bot's rules
    [[nodiscard]] int chooseCardPosition(const std::string &prompt) const override;

    //Answers yes/no questions using the bot's rules
    [[nodiscard]] bool askYesNo(const std::string &question) const override;

    //Stores a card the bot has seen in its own hand (outer cards, Peek, replacing)
    void remember(int pos, const Card &card) override;

private:
    //What the bot knows about its own four cards; known[i] is false if it has not seen card i
    Card memory[PlayHand::HAND_SIZE];
    bool known[PlayHand::HAND_SIZE];
};

#endif //PROJECT_BOT_HPP
