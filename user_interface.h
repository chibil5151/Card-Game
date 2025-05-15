#pragma once
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>
#include "winners_chart.h"
#include "leaderboard.h"
#include "card.h"
#include "deck.h"
#include "DynamicArray.h"
#include "game_manager.h"

class UserInterface {
public:
    static bool showInstructions();
    static std::string getPlayerName();
    static std::string getPlayerAnswer(const std::string& playerName, const Card& card);
    static void displayLeaderboard(const Leaderboard& leaderboard);

    static void showQuestionDetails(const Card& card);

    static void displayEndGameMenu(const DynamicArray<Player>& players, Leaderboard& leaderboard, const WinnersChart& winnersChart);
    static void displayWinnersChartMenu(const WinnersChart& winnersChart);
    static void searchWinnerChart(const WinnersChart& winnersChart);
    static void displayLeaderboardMenu(Leaderboard& leaderboard);
    static void searchLeaderboard(const Leaderboard& leaderboard);
    static void displaySortingMenu(Leaderboard& leaderboard);

    static int chooseDeck(const DiscardedDeck& discardedDeck);
    static int chooseCardFromDiscardedDeck();
    static void deckEmptyMessage(const std::string& deckName);
    static void invalidChoiceMessage();
    static bool askToAnswerQuestion(const Card& card);

};

#endif
