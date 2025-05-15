#include "winners_chart.h"
#include <iostream>
#include <iomanip> 

WinnersChart::WinnersChart() : root(nullptr) {}

void WinnersChart::addWinnerHelper(WinnersChartNode*& node, const Player& player) {
    if (node == nullptr) {
        node = new WinnersChartNode(player);
    }
    else if (player.getScore() > node->player.getScore()) {
        addWinnerHelper(node->left, player);
    }
    else {
        addWinnerHelper(node->right, player);
    }
}

void WinnersChart::addPlayers(const DynamicArray<Player>& players) {
    for (int i = 0; i < players.getSize(); ++i) {
        addWinner(players.at(i));
    }
}

void WinnersChart::addWinner(const Player& player) {
    addWinnerHelper(root, player);
}

WinnersChartNode* WinnersChart::searchWinnerHelper(WinnersChartNode* node, const std::string& name) const {
    if (node == nullptr) {
        return nullptr; // If node is null, return null
    }
    if (node->player.getName() == name) {
        return node;
    }
    if (name < node->player.getName()) {
        return searchWinnerHelper(node->left, name);
    }
    return searchWinnerHelper(node->right, name);
}

WinnersChartNode* WinnersChart::searchWinner(const std::string& name) const {
    return searchWinnerHelper(root, name);
}

void WinnersChart::inOrderTraversal(WinnersChartNode* node, WinnersChartNode** nodes, int& index, int count) const {
    if (node != nullptr && index < count) {
        inOrderTraversal(node->left, nodes, index, count);
        if (index < count) {
            nodes[index++] = node;
        }
        inOrderTraversal(node->right, nodes, index, count);
    }
}

void WinnersChart::displayTopWinners(int count) const {
    WinnersChartNode* nodes[30] = { nullptr }; // assuming count <= 30
    int index = 0;
    inOrderTraversal(root, nodes, index, count);

    // Define the column widths
    const int rankWidth = 6;
    const int nameWidth = 30;
    const int scoreWidth = 10;

    // Print table header
    std::cout << std::string(rankWidth + nameWidth + scoreWidth, '-') << std::endl;
    std::cout << std::left << std::setw(rankWidth) << "Rank"
        << std::left << std::setw(nameWidth) << "Player"
        << std::left << std::setw(scoreWidth) << "Score" << std::endl;
    std::cout << std::string(rankWidth + nameWidth + scoreWidth, '-') << std::endl;

    // Print table rows
    for (int i = 0; i < index; ++i) {
        if (nodes[i] != nullptr) {
            std::cout << std::left << std::setw(rankWidth) << i + 1
                << std::left << std::setw(nameWidth) << nodes[i]->player.getName()
                << std::left << std::setw(scoreWidth) << nodes[i]->player.getScore() << std::endl;
        }
    }
}


int WinnersChart::getPlayerRankHelper(WinnersChartNode* node, const std::string& name, int& rank) const {
    if (node == nullptr) {
        return -1; // Player not found
    }
    int leftRank = getPlayerRankHelper(node->left, name, rank);
    if (leftRank != -1) {
        return leftRank;
    }
    if (node->player.getName() == name) {
        return rank;
    }
    rank++;
    return getPlayerRankHelper(node->right, name, rank);
}

int WinnersChart::getPlayerRank(const std::string& name) const {
    int rank = 1;
    return getPlayerRankHelper(root, name, rank);
}
