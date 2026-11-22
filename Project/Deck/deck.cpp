//
// Created by jet on 9/28/26.
//
#include "deck.hpp"

#include <random>
#include <utility>

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

//Returns a vector of the numbers 0 to range-1 in a random order
std::vector<int> Deck::randomVector(int range) {
    std::vector<int> temp(range);
    for (int i = 0; i < range; i++) { // 0,1,2,3,...
        temp[i] = i;
    }

    //Seeded once; a new random_device every loop is slow and can repeat
    static std::mt19937 gen(std::random_device{}());

    for (int i = 0; i < range - 1; i++) {
        // get random number from i to the last index (range - 1)
        std::uniform_int_distribution<int> distr(i, range - 1);
        int random = distr(gen);
        std::swap(temp[i], temp[random]);
    }
    return temp;
}

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

//Copies the cards into a vector, then rebuilds the list in the order from randomVector()
void Deck::shuffle() {
    std::vector<Card> cards;
    for (Node<Card> *temp = cardList.getHead(); temp != nullptr; temp = temp->next)
        cards.push_back(temp->data);

    std::vector<int> order = randomVector(static_cast<int>(cards.size()));

    cardList.clear();
    for (int i: order) cardList.insertAtTail(cards[i]);
}

//Prints the whole deck
void Deck::printDeck(std::ostream &outs) const {
    int i = 1;
    for (Node<Card> *temp = cardList.getHead(); temp != nullptr; temp = temp->next)
        outs << i++ << ". " << temp->data << "\n";
}

//Builds the deck in the order given by randomVector() (see deck.hpp for the formula)
bool Deck::genDeck(int rankSize, int suitSize, int numJokers) {
    cardList.clear();

    if (rankSize < 1 || rankSize > static_cast<int>(Rank::King) ||
        suitSize < 1 || suitSize > static_cast<int>(Suit::Spades) + 1 || numJokers < 0) {
        std::cerr << "ERROR: Invalid deck size (ranks: " << rankSize << ", suits: "
                  << suitSize << ", jokers: " << numJokers << ")\n";
        return false;
    }

    const int numNormal = rankSize * suitSize; // cards that are not Jokers
    std::vector<int> temp = randomVector(numNormal + numJokers);

    for (int index: temp) {
        if (index < numNormal) {
            cardList.insertAtTail(Card(index, suitSize)); // index constructor does the rank/suit math
        } else {
            cardList.insertAtTail(Card(Rank::Joker, Suit::Clubs)); // suit unused for Jokers
        }
    }
    return true;
}
