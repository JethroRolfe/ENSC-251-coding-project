//
// Created by Jet on 11/2/2026.
//

#include "../deck.hpp"

//
// Created by jet on 9/28/26.
//
#include "deck.hpp"

#include "Card/card.hpp"

//Default constructor, (0 cards)
Deck::Deck() {}

//Deep copies a Deck with =
Deck &Deck::operator=(const deck &other) {
    if (this != &other) {
        singularLinkedList::clear();
        singularLinkedList::fromother(other);
    }
    return *this;
}

//Deep copies a Deck with copy constructor
Deck::Deck(Deck const &other) {
    singularLinkedList::copyfrom(other);
}

//Destructor
deck::~deck() {}


//Prints the whole deck
void deck::printDeck(std::ostream &outs) const {
    if (CardSystem::isEmpty()) {
        outs << "(empty)\n";
        return;
    }
    int i = 1;
    for (Node *temp = head; temp != nullptr; temp = temp->next)
        outs << i++ << ". " << temp->card << "\n";
}
