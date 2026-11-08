//
// Created by jet on 9/28/26.
//
// Deck: a pile of cards (same as Lab 2), stored in one singularLinkedList<Card>.
// The head of the list is the top of the pile.
// Added from the group doc: GenCards, Shuffle, randCardNum, peakCard.
//
// Design notes:
//  - Deck USES a linked list (composition) instead of inheriting it, because
//    that is how Lab 2 works and Jethro said Deck does not need to change.
//  - RemoveCard from the doc is drawTopCard().
//  - setNumCard is private: a deck is only ever empty or a full deck (group decision 11/7).
//  - orderCards dropped; the deck is shuffled instead (group decision 11/7).
//  - CardSystem left out (not described anywhere in the doc).
//
#ifndef PROJECT_DECK_HPP
#define PROJECT_DECK_HPP

#include "Card/card.hpp"
#include "Card/singularLinkedList.hpp"

class Deck {
private:
    singularLinkedList<Card> cardList;
    Node<Card> *head;
    int numCards;

    //syncs head with the private head
    void syncHead();

    //Random number from 0 to max-1, used by shuffle (group doc: randCardNum)
    static int randCardNum(int max);

    //Sets the card count; only used by genCards (full deck) or when emptying (group doc: setNumCard)
    void setNumCard(int n);

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

    //Fills the deck with Ace-10 of each suit + 2 Jokers.
    //If includePowerCards is true, also adds King, Queen, Jack (planned extension).
    //(group doc: GenCards)
    void genCards(bool includePowerCards);

    //Randomly reorders the cards (group doc: Shuffle)
    void shuffle();

    //Returns the top card without removing it (group doc: peakCard)
    [[nodiscard]] Card peekCard() const;

    //Prints the Deck
    void printDeck(std::ostream &outs) const;

    //Returns the highest card in the deck
    Card findHighCard() const;
};

#endif //PROJECT_DECK_HPP
