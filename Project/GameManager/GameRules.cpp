//
// Created by Jet on 11/24/2026.
//
#include "GameRules.hpp"
#include "DeckManager.hpp"
#include "player.hpp"

//powerCardsOn = false for the minimum game
GameRules::GameRules(bool powerCardsOn) : usePowers(powerCardsOn) {}

bool GameRules::powerCardsOn() const {
    return usePowers;
}

//Draws one card from the discard pile. It MUST replace one of the player's
//cards; the replaced card is discarded face up. A Power card can be taken
//from the discard pile but has no power.
void GameRules::drawFromDiscard(Player &player, DeckManager &decks) const {
    //Nothing to draw (discard pile is empty)
    if (decks.discardIsEmpty()) return;

    //Take the top card of the discard pile and store card in a temp
    player.getHand().addCard(decks.drawFromDiscard(), DeckChoice::DiscardPile);
    //replaced card is discarded face up
    placeTempCards(player, decks);
}

//Draws one card from the draw pile: the player replaces a card or discards it.
//A Power card goes to whatPowerCard().
void GameRules::drawFromDraw(Player **players, int numPlayers, int current, DeckManager &decks) const {
    Player &player = *players[current];
    Card temp = decks.drawFromPile();

    if (usePowers && temp.isFaceCard()) {
        whatPowerCard(temp, players, numPlayers, current, decks);
    } else {
        //Store card in a temp, then the player replaces a card or discards it
        player.getHand().addCard(temp, DeckChoice::DrawPile);
        placeTempCards(player, decks);
    }
}

//Switch on the face cards: Jack = Peek, Queen = Swap, King = Draw 2.
//Default: a normal card, which is replaced or discarded.
void GameRules::whatPowerCard(const Card &card, Player **players, int numPlayers, int current,
    DeckManager &decks) const {
    switch (static_cast<Rank>(card.getRank())) {
        case Rank::Jack:
            peek(*players[current]);
            break;
        case Rank::Queen:
            swap(players, numPlayers, current);
            break;
        case Rank::King:
            drawTwo(players, numPlayers, current, decks);
            break;
        default:
            //normal card is replaced or discarded
            players[current]->getHand().addCard(card, DeckChoice::DrawPile);
            placeTempCards(*players[current], decks);
            return;
    }
    //The power card is discarded
    decks.discard(card);
}

//End of round: replaces power cards with the top card of the draw pile.
//If another Power card is drawn, it goes to the discard pile and the player draws again.
void GameRules::replacePowerCards(PlayHand &hand, DeckManager &decks) const {
    //loop through Positions: 1-4
    for (int pos = 1; pos <= PlayHand::HAND_SIZE; ++pos) {
        if (hand.peekCard(pos)->isFaceCard()) { //if card is faceCard (power) do this ↓
            Card temp = decks.drawFromPile();                                           //store card in a temp

                                                                                        //While for if another Power card gets drawn ↓
            while (temp.isFaceCard()) {
                decks.discard(temp);                                                    //Discard card and draw again
                temp = decks.drawFromPile();
            }
                                                                                        //Put the new card in and discard the Power card
            decks.discard(hand.setCard(pos, temp));
        }
    }
}

//Replaces the player's power cards, then returns the hand's value (PlayHand::handScore)
int GameRules::scoreHand(Player &player, DeckManager &decks) const {
    replacePowerCards(player.getHand(), decks);
    return player.getHand().handScore();
}

//Explains a specific power card's rule
void GameRules::explainCard(const Card &card, std::ostream &outs) const {
    switch (static_cast<Rank>(card.getRank())) {
        case Rank::Jack:
            explainPeek(outs);
            break;
        case Rank::Queen:
            explainSwap(outs);
            break;
        case Rank::King:
            explainDrawTwo(outs);
            break;
        default:
            outs << card << " is not a power card. Value is: TODO\n";
            break;
    }
}

void GameRules::explainPeek(std::ostream &outs) const {
    outs << "Jacks are Peek cards \n They allow a player to look at any one of your own cards.\n Then end your turn.\n";
}

void GameRules::explainSwap(std::ostream &outs) const {
    outs << "Queens are Swap cards \n They allow a player to switch one of your cards with any card of another player\n"
         << "Without any players looking.\n Then end your turn.\n";
}

void GameRules::explainDrawTwo(std::ostream &outs) const {
    outs << "Kings are Draw 2 cards \n They allow a player to draw 2 cards, one at a time, from the draw or discard pile.\n"
             "Another Draw 2 starts the sequence again.\n Then end your turn.\n";
}

//Explains the player's available options
void GameRules::explainRules(std::ostream &outs) const {
    outs << "Each turn, pick one:\n"
         << "  1. Draw from the draw pile: swap it with one of your cards or discard it.\n"
         << "  2. Draw from the discard pile: you MUST swap it with one of your cards.\n";

    if (usePowers) {
        outs << "\nPower cards only work when drawn from the draw pile:\n";
        explainPeek(outs);
        explainSwap(outs);
        explainDrawTwo(outs);
    }

    outs << "\nAt the end of your turn you can knock to end the round.\n"
         << "Every other player gets one more turn, then the lowest hand score wins the round.\n";
}

//Peek: look at any one of your own cards. Everyone sees the peek (rules).
//Turn is over, the Peek card is discarded.
void GameRules::peek(Player &player) const {
    int pos = player.choosePosition("Which card do you want to peek at (1-4): ");

    std::cout << player.getName() << " peeks at card " << pos << ": "
              << *player.getHand().peekCard(pos) << std::endl;
    player.getHand().setKnown(pos, true);
}

//Swap: the Swap card is discarded; optionally switch one of your cards with any
//card of another player without looking. Both positions become unknown.
void GameRules::swap(Player **players, int numPlayers, int current) const {
    Player &player = *players[current];

    if (!player.askYesNo("Do you want to use the Swap? ")) return;

    int myPos = player.choosePosition("Which of your cards do you want to swap (1-4): ");
    int other = player.chooseOpponent(players, numPlayers, current);
    int theirPos = player.choosePosition("Which of " + players[other]->getName()
                                         + "'s cards do you want to swap (1-4): ");
    PlayHand &myHand = player.getHand();
    PlayHand &theirHand = players[other]->getHand();
    Card mine = *myHand.peekCard(myPos);
    Card theirs = theirHand.setCard(theirPos, mine);
    myHand.setCard(myPos, theirs);

    myHand.setKnown(myPos, false);
    theirHand.setKnown(theirPos, false);
}

//Draw 2: draw 2 cards, each from the discard pile (must be swapped in) or the
//draw pile, and hold them in the 2 temp locations. Then swap both, discard both,
//or swap one and discard the other.
//Another Draw 2: the cards already held must be swapped or discarded first,
//then the sequence starts again. Peek or Swap: used as one of the 2 draws.
void GameRules::drawTwo(Player **players, int numPlayers, int current, DeckManager &decks) const {
    Player &player = *players[current];

    for (int draws = 0; draws < 2; ++draws) {

        DeckChoice from = DeckChoice::DrawPile;
        if (!decks.discardIsEmpty()) from = player.whichDeck(decks.peekAtDiscard());

        if (from == DeckChoice::DiscardPile) {
            player.getHand().addCard(decks.drawFromDiscard(), DeckChoice::DiscardPile);
            continue;
        }

        Card temp = decks.drawFromPile();

        if (usePowers && static_cast<Rank>(temp.getRank()) == Rank::King) {
            placeTempCards(player, decks);
            whatPowerCard(temp, players, numPlayers, current, decks);
            return;
        }

        if (usePowers && temp.isFaceCard()) {
            whatPowerCard(temp, players, numPlayers, current, decks);
        } else {
            player.getHand().addCard(temp, DeckChoice::DrawPile);
        }
    }
    placeTempCards(player, decks);
}

//Asks the player to swap in or discard every card held in the temps
void GameRules::placeTempCards(Player &player, DeckManager &decks) const {
    PlayHand &hand = player.getHand();

    while (hand.hasTemp(1) || hand.hasTemp(2)) {
        int which;
        if (hand.hasTemp(1) && hand.hasTemp(2)) which = player.swapCardWith();
        else if (hand.hasTemp(1)) which = 1;
        else which = 2;


        int pos = player.swapCardPos(*hand.peekTemp(which), hand.mustReplace(which));

        if (pos == 0) decks.discard(hand.takeTemp(which));
        else decks.discard(hand.replaceCard(pos, which));
    }
}