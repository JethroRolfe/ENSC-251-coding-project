//
// Created by Jet on 11/21/2026.
//
#include "DeckManager.hpp"

//Constructor
//powerCards = false for the minimum game (42 cards)
DeckManager::DeckManager(bool powerCards) /* Sets values for min game or full game */ {
    if (powerCards) {rankSize = RANK_SIZE_Full_Game;}
    else {rankSize = RANK_SIZE_MIN_GAME;}

    suitSize = SUIT_SIZE;
    numJokers = NUM_JOKERS;
}

//Destructor (each Deck frees its own cards)
DeckManager::~DeckManager() {}

//-----------------------------------------------------------------------------
//Getter and setter

//Changes the deck that startNewRound() builds (custom decks)
void DeckManager::setDeckSize(int rankSize, int suitSize, int numJokers) {
    if (rankSize > 13 || rankSize < 1) { std::cerr << "Invalid Rank size: "<< rankSize << "\n"; return; }
    if (suitSize > 4 || suitSize < 1) { std::cerr << "Invalid Suit size: "<< suitSize << "\n"; return;}
    if (numJokers < 0) {std::cerr << "Invalid numJokers, Must be 0 or more: "<< numJokers << "\n"; return;}

    this->rankSize = rankSize;
    this->suitSize = suitSize;
    this->numJokers = numJokers;
}

//rankSize * suitSize + numJokers
int DeckManager::getDeckSize() const {return rankSize * suitSize + numJokers;}

//---------------------------------------------------------------------------------

//Empties both piles, builds a new shuffled draw pile with genDeck(),
//then flips the top card to start the discard pile. If that card is a Power
//card it is placed back in the deck and another card is turned over (rules: Set-up).
void DeckManager::startNewRound() {
    drawPile.clear();
    discardPile.clear();

    if (!drawPile.genDeck(rankSize, suitSize, numJokers)) return; // invalid size
    Card topCard = drawPile.peekTopCard();
    while ( topCard.isFaceCard()) {
        shuffle();
        topCard = drawPile.peekTopCard();
    }
    discard(drawFromPile());
}

//Shuffles the draw pile into a random order
void DeckManager::shuffle() {
    drawPile.shuffle();
}

//Deals 4 cards to a player's hand
void DeckManager::deal(PlayHand &hand) {
    for (int i = 1; i <= PlayHand::HAND_SIZE; i++) {
        hand.setCard(i, drawFromPile());
    }
}

//Draws the top card from the active draw pile (returns + removes it).
//Calls refillDrawPile() first if the draw pile is empty.
Card DeckManager::drawFromPile() {
    if (drawPile.isEmpty()) {
        refillDrawPile();
    }
    return drawPile.drawTopCard();
}

//Draws the top card from the discard pile (returns + removes it)
Card DeckManager::drawFromDiscard() {
    return discardPile.drawTopCard();
}

//Returns the top card of the discard pile without removing it
Card DeckManager::peekAtDiscard() const {
    return discardPile.peekTopCard();
}

bool DeckManager::discardIsEmpty() const {
    return discardPile.isEmpty();
}

//Places a card face up on the discard pile
void DeckManager::discard(const Card &c) {
    discardPile.addCard(c);
}

//Rules: when the draw pile runs out, the discard pile except its top card is
//shuffled into a new draw pile; the top card stays face up as the discard pile
void DeckManager::refillDrawPile() {
    if (discardPile.getNumCards() > 1) {
        Card topDiscardCard = discardPile.drawTopCard(); //stores card so top card of discard pile stays

        while (!discardPile.isEmpty()) {
            drawPile.addCard(drawFromDiscard());
        }
        drawPile.shuffle();
        discard(topDiscardCard);
    }
}

//Shows the top of the discard pile
void DeckManager::printDiscard(std::ostream &outs) const {
    if (!discardPile.isEmpty()) {
        outs << discardPile.peekTopCard() << "\n";
        outs << "Discard Pile Size : "<< discardPile.getNumCards() << "\n";
    }
    else { outs << "Empty Discard Pile" << "\n"; }
}


















