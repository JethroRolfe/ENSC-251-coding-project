//
// Created by Jet on 11/21/2026.
//
#include "DeckManager.hpp"

//powerCards = false for the minimum game (42 cards)
DeckManager::DeckManager(bool powerCards) {
}

//Destructor (each Deck frees its own cards)
DeckManager::~DeckManager() {
}

//Changes the deck that startNewRound() builds (custom decks)
void DeckManager::setDeckSize(int rankSize, int suitSize, int numJokers) {
}

//rankSize * suitSize + numJokers
int DeckManager::getDeckSize() const {
}

//Empties both piles, builds a new shuffled draw pile with genIndex() + genDeck(),
//then flips the top card to start the discard pile. If that card is a Power
//card it is placed back in the deck and another card is turned over (rules: Set-up).
void DeckManager::startNewRound() {
}

//Shuffles the draw pile into a random order
void DeckManager::shuffle() {
}

//Deals 4 cards to a player's hand
void DeckManager::deal(PlayHand &hand) {
}

//Draws the top card from the active draw pile (returns + removes it).
//Calls refillDrawPile() first if the draw pile is empty.
Card DeckManager::drawFromPile() {
}

//Draws the top card from the discard pile (returns + removes it)
Card DeckManager::drawFromDiscard() {
}

//Returns the top card of the discard pile without removing it
Card DeckManager::peekAtDiscard() const {
}

bool DeckManager::discardIsEmpty() const {
}

//Places a card face up on the discard pile
void DeckManager::discard(const Card &c) {
}

//Rules: when the draw pile runs out, the discard pile except its top card is
//shuffled into a new draw pile; the top card stays face up as the discard pile
void DeckManager::refillDrawPile() {
}

//Shows the top of the discard pile
void DeckManager::printDiscard(std::ostream &outs) const {
}




















