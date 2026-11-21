//
// Created by jet on 9/28/26.
//
#include "deck.hpp"

#include <algorithm>
#include <random>

//Default constructor, Creates an empty deck (0 cards)
Deck::Deck() = default;

//Deep copies a Deck with =
Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        cardList.clear();
        for (Node<Card> *temp = other.cardList.getHead(); temp != nullptr; temp = temp->next)
            cardList.insertAtTail(temp->data);
    }
    return *this;
}

//Deep copies a Deck with copy constructor
Deck::Deck(Deck const &other) {
    for (Node<Card> *temp = other.cardList.getHead(); temp != nullptr; temp = temp->next)
        cardList.insertAtTail(temp->data);
}

//Checks if deck is Empty
bool Deck::isEmpty() const { return cardList.isEmpty(); }

//Gets num of Cards in a deck
int Deck::getNumCards() const { return cardList.getCount(); }

//Draws the top card and returns it
Card Deck::drawTopCard() {
    if (cardList.isEmpty()) {
        std::cerr << "You tried to draw a Card with 0 Cards available\n";
        return Card();
    }
    Card c = cardList.getHead()->data;
    cardList.deleteFromHead();
    return c;
}

//Adds a specific card to the top of the deck
bool Deck::addCard(const Card &c) {
    cardList.insertAtHead(c);
    return true;
}

//Top card without removing it
Card Deck::peekTopCard() const {
    if (cardList.isEmpty()) return Card();
    return cardList.getHead()->data;
}

void Deck::clear() { cardList.clear(); }

//Prints the whole deck
void Deck::printDeck(std::ostream &outs) const {
    int i = 1;
    for (Node<Card> *temp = cardList.getHead(); temp != nullptr; temp = temp->next)
        outs << i++ << ". " << temp->data << "\n";
}

//Builds the deck in the order given by index (see deck.hpp for the formula)
void Deck::genDeck(const int index[], const int size, const int rankSize, const int suitSize) {
    cardList.clear();
    for (int i = 0; i < size; i++) {
        const int k = index[i];
        if (k >= rankSize * suitSize) {
            cardList.insertAtTail(Card(Rank::Joker, Suit::Clubs));
        } else {
            cardList.insertAtTail(Card(k / suitSize + 1, k % suitSize));
        }
    }
}

//Shuffled array of 0 to size-1
std::vector<int> Deck::genIndex(const int size) {
    std::vector<int> index(size);
    for (int i = 0; i < size; i++) index[i] = i;
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(index.begin(), index.end(), rng);
    return index;
}
