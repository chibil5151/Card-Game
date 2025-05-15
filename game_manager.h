#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "card.h"
#include "deck.h"
#include "player.h"
#include "winners_chart.h"
#include "leaderboard.h"
#include "file_io.h"
#include "user_interface.h"
#include "DynamicArray.h"

class GameManager {
public:
    GameManager();
    ~GameManager();
    void startGame();
    void playRound(int i);
    void endGame();

    
private:
    UnansweredDeck unansweredDeck;
    AnsweredDeck answeredDeck;
    DiscardedDeck discardedDeck;
    WinnersChart winnersChart;
    Leaderboard leaderboard;

    DynamicArray<std::string> topics;
    DynamicArray<Player> players;
    Player player;
    void setupPlayers();
};

#endif

