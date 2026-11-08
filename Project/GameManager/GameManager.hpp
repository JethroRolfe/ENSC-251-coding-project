//
// Created by Jet on 11/7/2026.
//
// GameManager: uses objects of Player, as many as players in the game.
// Manages the game and decides whose turn it is (group doc).
// Minimum viable game: 2 player local game played in the terminal.
//
// Group decisions (11/7):
//  - 2 to 3 players (official rules allow 2-6; capped at 3 because of
//    hot-seat play on one keyboard and terminal).
//  - Hidden cards: "It's Player 2's turn, press Enter to confirm you are Player 2"
//    before each turn (also goes in Technical Challenges in the design doc).
//  - Players array holds Player pointers so it can also hold Bots.
//
// PROPOSED (still undecided by the group):
//  - End of game: official option 3. A player who reaches 100 points is out;
//    the last player left in the game is the winner (Jethro: "players dropping
//    out is cool, it's more competitive").
//
#ifndef PROJECT_GAMEMANAGER_HPP
#define PROJECT_GAMEMANAGER_HPP

#include "../Player/player.hpp"
#include "../Deck/DeckManager.hpp"

class GameManager {
public:
    static const int MIN_PLAYERS = 2;
    static const int MAX_PLAYERS = 3;
    static const int SCORE_LIMIT = 100;

    //Creates numPlayers players (MIN_PLAYERS to MAX_PLAYERS).
    //powerCardsOn = false for the minimum viable game.
    GameManager(int numPlayers, bool powerCardsOn = false);

    //Destructor: deletes every player, then the players array
    ~GameManager();

    //No copying (owns dynamic memory)
    GameManager(const GameManager &) = delete;

    GameManager &operator=(const GameManager &) = delete;

    //Runs the whole game: rounds until the game ends, then shows the winner
    void play();

private:
    Player **players; // dynamic array of numPlayers Player pointers (Player or Bot)
    int numPlayers;
    int dealer;       // index of the dealer
    int current;      // index of the player whose turn it is
    int knocker;      // index of the player who knocked, -1 if nobody has
    bool usePowers;
    DeckManager decks;

    //Asks each player for their name
    void setupPlayers();

    //One round: set-up, turns until a knock, then scoring
    void playRound();

    //Set-up (official rules): shuffle, player left of the dealer cuts,
    //dealer deals four cards one at a time face down to each player,
    //then the first card is turned over to start the discard pile
    void dealCards();

    //Players peek at their two outer cards once, then turn them face down again
    void peekOuterCards();

    //One player's turn: draw from the discard pile or the draw pile,
    //then Player::ruleCheck. At the end of the turn the player may knock.
    void takeTurn();

    //Decides whose turn is next (play continues to the left / clockwise)
    void nextPlayer();

    //Ending the round (official rules): after a knock every other player has
    //one more turn, players turn over their cards, replace power cards,
    //and add the point values of their four cards
    void endRound();

    //The player to the left of the dealer deals the next round
    void nextDealer();

    //True when only one player is left under SCORE_LIMIT
    [[nodiscard]] bool isGameOver() const;

    //Shows final scores; the last player left in the game is the winner
    void announceWinner() const;

    //Clears the screen and shows "It's <name>'s turn, press Enter to confirm
    //you are <name>", so players cannot see each other's cards
    void passToNextPlayer() const;

    //Clears the terminal with the ANSI codes "\033[2J\033[H"
    static void clearScreen();
};

#endif //PROJECT_GAMEMANAGER_HPP
