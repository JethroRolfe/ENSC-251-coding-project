//
// Bot: computer-controlled player (planned extension).
//

#include "Bot.hpp"

Bot::Bot(const std::string &name) {
}

bool Bot::isBot() const {
    return Player::isBot();
}

DeckChoice Bot::whichDeck(const Card &topDiscard) {
    return Player::whichDeck(topDiscard);
}

int Bot::swapCardPos(const Card &drawn, bool mustReplace) {
    return Player::swapCardPos(drawn, mustReplace);
}

int Bot::swapCardWith() {
    return Player::swapCardWith();
}

int Bot::choosePosition(const std::string &prompt) {
    return Player::choosePosition(prompt);
}

int Bot::chooseOpponent(Player **players, int numPlayers, int self) {
    return Player::chooseOpponent(players, numPlayers, self);
}

bool Bot::askYesNo(const std::string &question) {
    return Player::askYesNo(question);
}

bool Bot::knock() {
    return Player::knock();
}

int Bot::worstKnownPos() const {
}

int Bot::knownScore() const {
}
