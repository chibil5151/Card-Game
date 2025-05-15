#pragma once
#ifndef WINNERS_CHART_H
#define WINNERS_CHART_H

#include "player.h"
#include "DynamicArray.h"

class WinnersChartNode {
public:
    Player player;
    WinnersChartNode* left;
    WinnersChartNode* right;
    WinnersChartNode(const Player& player) : player(player), left(nullptr), right(nullptr) {}
};

class WinnersChart {
public:
    WinnersChart();
    void addPlayers(const DynamicArray<Player>& players);
    void addWinner(const Player& player);
    WinnersChartNode* searchWinner(const std::string& name) const;
    void displayTopWinners(int count) const;
    int getPlayerRank(const std::string& name) const;

private:
    WinnersChartNode* root;
    void addWinnerHelper(WinnersChartNode*& node, const Player& player);
    WinnersChartNode* searchWinnerHelper(WinnersChartNode* node, const std::string& name) const;
    void inOrderTraversal(WinnersChartNode* node, WinnersChartNode** nodes, int& index, int count) const;
    int getPlayerRankHelper(WinnersChartNode* node, const std::string& name, int& rank) const;
};

#endif
