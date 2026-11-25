// created by ayden on 11/23/2026

#include "player.hpp"
using namespace std;

// public

// constructors

//Default constructor
Player::Player()
 : totalScore(0), isOut(false), firstTurnKnocks(0), worstRound(0) {

}

//Constructor with the player's name
Player::Player(const string& name)
 : name(name), totalScore(0), isOut(false), firstTurnKnocks(0), worstRound(0) {
    
}

//Getters / setters

string Player::getName() const { // name getter
    return name;
}

const PlayHand& Player::getHand() const {
    return hand;
}

PlayHand& Player::getHand() { // hand getter (returns address of hand)
    return hand;
}

void Player::setName(const string& newName) { // name setter
    name = newName;
}

int Player::getTotalScore() const { // totalScore getter
    return totalScore;
}

bool Player::getIsOut() const { // isOut getter
    return isOut;
}

bool Player::isBot() const {
    return false;
}

// input functions with cin

//Asks the player to draw from the draw pile or the discard pile
DeckChoice Player::whichDeck(const Card &topDiscard) {
    cout << "take a card from the stock pile (1) or discard pile (2)?\n";
    int deckChoice = Player::readInt(1, 2);
    if (deckChoice == 1) {
        return DeckChoice::DrawPile;
    }
    else {
        return DeckChoice::DiscardPile;
    }
}

//Asks which position (1-4) to swap the drawn card into, or 0 to discard it.
//mustReplace = true (card from the discard pile): 0 is not allowed.
int Player::swapCardPos(const Card &drawn, bool mustReplace) {
    cout  << "swap with which position? (1, 2, 3, 4, 0 to discard)\n";
    if (!mustReplace) {
        return readInt(0, 4);
    }
    else {
        return readInt(1, 4);
    }
}

//Draw 2: asks which held card to place next, temp 1 or temp 2
int Player::swapCardWith() {
    cout << "place first held card (1) or second held card (2)?\n";
    return Player::readInt(1, 2);
}

//Asks for one of the player's positions 1-4 (Peek, Swap, reordering)
int Player::choosePosition(const std::string &prompt) {
    cout << "which position would you like to " << prompt << "? (1, 2, 3, or 4)\n";
    return Player::readInt(1, 4);
}

//Swap: asks which other player to swap with; returns their index
// ayden: assumes player array indexed from 0 to numPlayers
int Player::chooseOpponent(Player **players, int numPlayers, int self) {
    cout << "which opponent would you like to to swap with?\n";
    for (int p = 0; p < numPlayers; p++) {
        cout << "(" << p + 1 << ") " << players[p]->getName() << endl;
    }

    int oppToSwap = Player::readInt(1, numPlayers);
    if (oppToSwap != self) {
        return oppToSwap;
    }
    else {
        cout << "error: you may not swap cards with yourself.\n";
        return Player::chooseOpponent(players, numPlayers, self);
    }
}

//Yes/no questions: shuffle request, reorder at the peek, use Swap
bool Player::askYesNo(const std::string &question) {
    cout << question << " (1) for yes, (2) for no\n";
    int yorn = readInt(1, 2);
    if (yorn == 1) {
        return true;
    }
    else {
        return false;
    }
}

//Asks if the player knocks (ends the round) at the end of their turn
bool Player::knock() {
    string knockQuestion = "end of turn. would you like to knock?";
    return askYesNo(knockQuestion);
}

// scoring

//Adds the end of round score to the total score and keeps the worst round
void Player::addScore(int roundScore) {
    totalScore = totalScore + roundScore;
    if (roundScore > worstRound) {
        worstRound = roundScore;
    }
    return;
}

//Knock tracking (rules): call once per round. Returns the penalty to add.
int Player::recordFirstTurnKnock(bool knockedOnFirstTurn) {
    if (knockedOnFirstTurn) {
        firstTurnKnocks++;
        if (firstTurnKnocks > 1) {
            return firstTurnKnocks;
        }
        else {
            return 0;
        }
    }
    else {
        firstTurnKnocks = 0;
        return 0;
    }
}

//Sets isOut when totalScore reaches scoreLimit
void Player::updateIsOut(int scoreLimit) {
    if (totalScore >= scoreLimit) {
        isOut = true;
    }
    else {
        isOut = false;
    }
    return;
}

//End screen stats
int Player::getWorstRound() const {
    return worstRound;
}

// protected

// helper function that checks for valid indices
int Player::readInt(int min, int max) {
    int input;
    while (true) { // repeat until return
        cin >> input;
        if (cin.fail()) {
            cout << "error: input must be an integer, please try again.";
            cin.clear();
            cin.ignore(100, '\n');
        }
        else if (input < min || input > max) {
            cout << "erorr: input must be an integer between " << min << " and " << max << 
            ". please try again.\n";
        }
        else {
            return input;
        }
    }
}
