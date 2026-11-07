//
// Created by Jet on 11/2/2026.
//

#ifndef PROJECT_DECK_HPP
#define PROJECT_DECK_HPP
#include "Card/CardSystems/cardSystem.hpp"


class Deck : public CardSystem {

    //Default constructor
    Deck();

    //Deep copies a Deck with =
    Deck &operator=(const deck &other);

    //Deep copies a Deck with copy constructor
    Deck(Deck const &other);

    //Destructor
    ~Deck();

    //Prints the Deck
    void printDeck(std::ostream &outs) const;

};


#endif //PROJECT_DECK_HPP
