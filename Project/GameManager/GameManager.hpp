//
// Created by Jet on 11/7/2026.
//
// GameManager: manages the game. Decides whose turn it is, the winner, and setup.
// Owns the players, the DeckManager and the GameRules.
//
// Rules used here:
//  - The game deals and keeps score. Player 1 goes first; each new round the
//    first player moves on by one (bots included).
//  - Everyone sees every peek, so cards are not hidden between turns.
//  - The first player may request one shuffle per round, before any card is drawn.
//  - At the initial peek each player sees their two outer cards and may reorder
//    their cards once.
//  - Knocking: only at the end of your own turn; after a knock every other player
//    has one more turn, then the round ends.
//  - A player whose total reaches scoreLimit is out; the last player in wins.
//    With 2 players the game ends as soon as one is out; if both pass the limit in
//    the same round, the lower total wins.
//
#ifndef PROJECT_GAMEMANAGER_HPP
#define PROJECT_GAMEMANAGER_HPP

#include "../Player/player.hpp"
#include "../Deck/DeckManager.hpp"
#include "GameRules.hpp"

class GameManager {
public:
    static const int MIN_PLAYERS = 2;
    static const int MAX_PLAYERS = 6;       // official rules allow 2-6
    static const int DEFAULT_SCORE_LIMIT = 100;

    //powerCardsOn = false for the minimum game
    explicit GameManager(bool powerCardsOn = false);

    //Destructor: deletes every player, then the players array
    ~GameManager();

    //No copying (owns dynamic memory)
    GameManager(const GameManager &) = delete;

    GameManager &operator=(const GameManager &) = delete;

    //Sets up the game: number of players, names, and if each one is a bot
    void setup();

    //Main loop: runs rounds until the game ends, then displays the winner
    void play();

    //Score limit can be changed (rules: play to 100, 200, or any other number)
    void setScoreLimit(int limit);

    [[nodiscard]] int getScoreLimit() const;

private:
    Player **players;        // array of players (2 in the minimum game), Player or Bot
    int numPlayers;          // number of players
    DeckManager deckManager; // the draw and discard piles
    GameRules rules;         // applies the rules
    int currentPlayer;       // index of whose turn it is
    int firstPlayer;         // index of who goes first this round (moves +1 each round)
    int iAmTheOneWhoKnocks;  // index of who knocked, -1 if nobody has
    int round;               // current round number
    int turnsThisRound;      // used to tell if it is a player's first turn of the round
    int scoreLimit;          // score that, if reached, kicks a player from the game
    bool easyMode;           // "For Younger Players": known cards are shown

    //Calls startNewRound() and deal(), offers the shuffle request, then publicly
    //shows everyone's peek at their outer cards (positions 1 and 4)
    void startRound();

    //Rules: the first player can request one shuffle per round before any card is drawn
    void offerShuffle();

    //Each player peeks at their outer cards (shown to everyone) and may reorder once
    void peekOuterCards();

    //Runs one turn for currentPlayer (discard pile or draw pile through GameRules),
    //then asks if they knock
    void playTurn();

    //Moves currentPlayer to the next player who is not out
    void nextPlayer();

    //Called when the turn comes back to iAmTheOneWhoKnocks: reveals all hands,
    //replaces power cards, adds scores and first-turn knock penalties, updates
    //who is out, and moves firstPlayer on by one
    void endRound();

    //Collects every card from the hands (the piles are rebuilt by startNewRound)
    void collectCards();

    //True when only one player is not out (or none, if both went out together)
    [[nodiscard]] bool isGameOver() const;

    //Prints who won and some stats: placements, scores, worst round
    void displayWinner() const;
};

#endif //PROJECT_GAMEMANAGER_HPP
