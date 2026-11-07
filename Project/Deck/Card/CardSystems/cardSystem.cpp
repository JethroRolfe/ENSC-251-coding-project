//
// Created by Jet on 11/2/2026.
//

#include "cardSystem.hpp"



CardSystem::CardSystem() {}
CardSystem::~CardSystem() { singularLinkedList::clear(); }


//Gets number of Cards in a deck
int CardSystem::getNumCards() const { return singularLinkedList::getCount(); }

//Removes the top card and returns that card
card CardSystem::drawTopCard() {
    Card c1 = singularLinkedList::getHead();
    singularLinkedList::deleteFromHead();
    return c1;
}

//Adds a card at the top
bool CardSystem::addCardAtTop(card c) {
    bool result = false;
    singularLinkedList::insertIntoHead(c);
    result = true;
}

//Adds a card at the bottem
bool CardSystem::addCardAtBottem(card c) {
    bool result = false;
    singularLinkedList::insertIntoTail(c);
    result = true;
}

//IsEmpty
bool CardSystem::isEmpty() {
    return singularLinkedList::isEmpty();
    }
};