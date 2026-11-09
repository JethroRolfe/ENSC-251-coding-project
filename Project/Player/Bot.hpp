//
// Bot: a computer-controlled player (planned extension).
// Inherits Player and answers the input functions with its own rules instead
// of asking a person. It only uses the cards it knows (PlayHand::isKnown).
//
// Rules: bots only knock on their first turn if their known cards are low.
// TODO (group): decide the rest of the bot's rules (when to take the discard,
// when to replace a card, when to use a power).
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

    [[nodiscard]] bool isBot() const override;

    [[nodiscard]] DeckChoice whichDeck(const Card &topDiscard) override;

    [[nodiscard]] int swapCardPos(const Card &drawn, bool mustReplace) override;

    [[nodiscard]] int swapCardWith() override;

    [[nodiscard]] int choosePosition(const std::string &prompt) override;

    [[nodiscard]] int chooseOpponent(Player **players, int numPlayers, int self) override;

    [[nodiscard]] bool askYesNo(const std::string &question) override;

    [[nodiscard]] bool knock() override;

private:
    //Known card with the highest value, or an unknown position if any (1-4)
    [[nodiscard]] int worstKnownPos() const;

    //Sum of the known cards, used to decide when to knock
    [[nodiscard]] int knownScore() const;
};

#endif //PROJECT_BOT_HPP

//added for a diff, no comment was add to the push :(