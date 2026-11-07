//
// Created by jet on 9/28/26.
//
#ifndef LAB2_DECK_HPP
#define LAB2_DECK_HPP

#include "Card.hpp"
#include "Card/singularLinkedList.hpp"

class Deck {
private:
    singularLinkedList<Card> cardList;
    Node<Card> *head;
    int numCards;

    //syncs head with the private head
    void syncHead();

public:
    //Default constructor
    Deck();

    //Deep copies a Deck with =
    Deck &operator=(const Deck &other);

    //Deep copies a Deck with copy constructor
    Deck(Deck const &other);

    //Destructor
    ~Deck();

    [[nodiscard]] bool isEmpty() const;

    //Getter
    [[nodiscard]] int getNumCards() const;

    //Draw Top card (the head)
    Card drawTopCard();

    //Adds a card at the top (the head)
    bool addCard(Card c);

    //Prints the Deck
    void printDeck(std::ostream &outs) const;

    //Returns the highest card in the deck
    Card findHighCard() const;
};

#endif //LAB2_DECK_HPP
