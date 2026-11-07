//
// Created by Jet on 11/2/2026.
//

#ifndef PROJECT_CARDSYSTEM_HPP
#define PROJECT_CARDSYSTEM_HPP
#include "singularLinkedList.hpp"

class CardSystem : public singularLinkedList<Card> {
    protected:
    CardSystem();

    //Delete any shallow copies made
    CardSystem(const singularLinkedList &) = delete;

    CardSystem &operator=(const singularLinkedList &) = delete;

    ~CardSystem();

    //Getter
    [[nodiscard]] int getNumCards() const;

    //Draw Top card (the head)
    Card drawTopCard();

    //Adds a card at the top (the head)
    bool addCard(Card c);

    bool isEmpty();
};


#endif //PROJECT_CARDSYSTEM_HPP
