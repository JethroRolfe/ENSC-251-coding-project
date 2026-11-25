// created by ayden on 11/23/2026

// for the following code:
// i am assuming pos is 1-4 not the actual indices 0-3
// please change if it doesnt work. - ayden

#include "PlayHand.hpp"
using namespace std;

// constructors

PlayHand::PlayHand() { // default constructor
    clear();
}

//Puts a dealt card at pos (1-4) and returns the card that was there
Card PlayHand::setCard(int pos, const Card &c) {
    Card tempCard = cards[pos - 1];
    cards[pos - 1] = c;
    return tempCard;
}

// accessors
// they all assume whichTemp is valid, so it must be checked upon input

//Adds a drawn card to the first free temp location; from = which pile it came from.
//Returns the temp number used (1 or 2), or 0 if both temps are full.
int PlayHand::addCard(const Card &c, DeckChoice from) {
    if (!tempUsed[0]) {
        cards[4] = c;
        tempUsed[0] = true;
        tempFrom[0] = from;
        return 1;
    }
    else if (!tempUsed[1]) {
        cards[5] = c;
        tempUsed[1] = true;
        tempFrom[1] = from;
        return 2;  
    }
    else {
        return 0;
    }
}

//Swaps temp 1 or temp 2 into position pos (1-4). Returns the old card, which goes
//to the discard pile. The new card at pos is now known to the player.
Card PlayHand::replaceCard(int pos, int whichTemp) {
    Card toDiscard = cards[pos - 1]; // temp card to return
    cards[pos - 1] = cards[HAND_SIZE - 1 + whichTemp];
    tempUsed[whichTemp - 1] = false; // it becomes an open slot by name
    return toDiscard; // return old card to the discard pile
}

//Removes the card in temp 1 or temp 2 so it can be discarded.
// ayden: assumes whichTemp is indexed 1-2 not 0-1
//Not allowed if it came from the discard pile (mustReplace).
Card PlayHand::takeTemp(int whichTemp) {
    // fails if it came straight from discard
    if (!mustReplace(whichTemp)) {
        Card takenOut = cards[HAND_SIZE - 1 + whichTemp]; // temp card to return
        tempUsed[whichTemp - 1] = false; // it becomes an open slot by name
        return takenOut;
    }
    else {
        return Card{};
    }
}

bool PlayHand::hasTemp(int whichTemp) const {
    return tempUsed[whichTemp - 1];
}

//True if the temp card came from the discard pile and must be swapped in
// ayden: assumes whichTemp is indexed 1-2 not 0-1

bool PlayHand::mustReplace(int whichTemp) const {
    if(tempFrom[whichTemp - 1] == DeckChoice::DiscardPile) {
        return true;
    }
    else { // (implicit) if its from the draw pile
        return false;
    }
}

//Returns the card at pos (1-4) without changing it, for cout << *peekCard(pos)
const Card* PlayHand::peekCard(int pos) const {
    return &cards[pos - 1];
}

//Returns the card in temp 1 or temp 2, nullptr if empty
// ayden: assumes whichTemp is indexed 1-2 not 0-1
const Card* PlayHand::peekTemp(int whichTemp) const {
    if (tempUsed[whichTemp - 1]) {
        return &cards[HAND_SIZE - 1 + whichTemp];
    }
    else {
        return nullptr;
    }
}

//Reorders two of the player's cards (allowed once, at the initial peek)
void PlayHand::swapPositions(int posA, int posB) {
    if (isValidPos(posA) && isValidPos(posB) && posA != posB) {
        Card tempForSwap = cards[posA - 1];
        cards[posA - 1] = cards[posB - 1];
        cards[posB - 1] = tempForSwap;
    }
    return;
}


//Checks if position is between 1 and 4
bool PlayHand::isValidPos(int pos) const {
    if (pos >= 1 && pos <= 4) {
        return true;
    }
    else {
        return false;
    }
}

//Known cards: shown in easy mode, and used by bots
bool PlayHand::isKnown(int pos) const {
    if(PlayHand::isValidPos(pos) && known[pos - 1]) {
        return true;
    }
    else {
        return false;
    }
}

// ayden: some kind of inverse operation? thats how i interpreted it
void PlayHand::setKnown(int pos, bool isKnown) {
    known[pos - 1] = isKnown;
    return;
}

void PlayHand::clear() {
    for (int i = 0; i < HAND_SIZE + TEMP_SIZE; i++) {
       cards[i] = Card{}; // call default constructor
    }
    for (int j = 0; j < TEMP_SIZE; j++) {
       tempUsed[j] = false; // reset both temp to not used
    }
    for (int k = 0; k < HAND_SIZE; k++) {
       known[k] = false; // reset all hand to not known
    }
    return;
}
//Prints the hand as [?] [?] [?] [?]; in easy mode the known cards are revealed
void PlayHand::printHidden(std::ostream &outs, bool easyMode) const {
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            outs << " ";
        }
        if (easyMode && known[i]) {
            outs << "[" << cards[i] << "]";
        }
        else {
            outs << "[?]";
        }
    }
    outs << endl;
}
//Prints all four cards at the end of the round
void PlayHand::printRevealed(std::ostream &outs) const {
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            outs << " ";
        }
        outs << "[" << cards[i] << "]";
    }
    outs << endl;
}
//Returns the value of the hand: sum of rankValue() of the 4 cards
int PlayHand::handScore() const {
    int tempScore = 0;
    for (int i = 0; i < HAND_SIZE; i++) {
        tempScore = tempScore + cards[i].rankValue();
    }
    return tempScore;
}


