#pragma once
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "player.h"
#include "card.h"
#include "DynamicArray.h"
#include <string>

class LeaderboardNode {

public:
    Player player;
    LeaderboardNode* next;
    LeaderboardNode(const Player& player)
        : player(player), next(nullptr) {}
};

class Leaderboard {
public:
    Leaderboard();
    void addPlayerEntry(const Player& player);
    void addPlayerEntries(const DynamicArray<Player>& players);
    void sortLeaderboardHelper(LeaderboardNode*& head, bool ascending);
    void sortLeaderboard();
    void sortLeaderboardByLowestScore();
    void displayLeaderboard() const;
    LeaderboardNode* searchPlayer(const std::string& name) const;

private:
    LeaderboardNode* head;
    void displayLeaderboardHelper(LeaderboardNode* node) const;
    LeaderboardNode* searchPlayerHelper(LeaderboardNode* node, const std::string& name) const;
};

#endif
