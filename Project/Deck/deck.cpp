//
// Created by jet on 9/28/26.
//
#include "Deck.hpp"

#include "singularLinkedList.hpp"

//Default constructor, Creates an empty deck (0 cards)
Deck::Deck() : cardList(nullptr), head(cardList.getHead()), numCards(0) {
}

//Deep copies a Deck with =
Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        cardList.clear();
        for (Node<Card> *temp = other.head; temp != nullptr; temp = temp->next)
            cardList.insertAtTail(temp->data);
        syncHead();
        numCards = other.numCards;
    }
    return *this;
}

//Deep copies a Deck with copy constructor
Deck::Deck(Deck const &other) : cardList(nullptr), head(nullptr), numCards(other.numCards) {
    for (Node<Card> *temp = other.head; temp != nullptr; temp = temp->next)
        cardList.insertAtTail(temp->data);
    syncHead();
}

//Destructor
Deck::~Deck() {
}

//Checks if deck is Empty
bool Deck::isEmpty() const {
    return (numCards == 0 || cardList.isEmpty());
}

//Gets num of Cards in a deck
int Deck::getNumCards() const { return numCards; }

//Draws the top card and return a card object
[[nodiscard]] Card Deck::drawTopCard() {
    if (cardList.isEmpty()) {
        std::cout << "You tried to draw a Card with 0 Cards available \n";
        return Card();
    }
    Card c = head->data;
    cardList.deleteFromHead();
    syncHead();
    numCards--;
    return c;
}

//adds a specific card to the deck
bool Deck::addCard(Card c) {
    cardList.insertAtHead(c);
    syncHead();
    numCards++;
    return true;
}

//Prints the whole deck
void Deck::printDeck(std::ostream &outs) const {
    int i = 1;
    for (Node<Card> *temp = head; temp != nullptr; temp = temp->next)
        outs << i++ << ". " << temp->data << "\n";
}

//Returns the highest card in the deck (AceHigh is in rankValue in Card)
Card Deck::findHighCard() const {
    if (head == nullptr) return Card();
    Card highest = head->data;
    for (Node<Card> *temp = head->next; temp != nullptr; temp = temp->next)
        if (temp->data > highest) highest = temp->data;
    return highest;
}

//syncs head with the private head
void Deck::syncHead() {
    head = cardList.getHead();
}
