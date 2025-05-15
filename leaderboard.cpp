#include "leaderboard.h"
#include <iostream>
#include <iomanip> 

Leaderboard::Leaderboard() : head(nullptr) {}

void Leaderboard::addPlayerEntry(const Player& player) {
    LeaderboardNode* newNode = new LeaderboardNode(player);
    newNode->next = head;
    head = newNode;
}

void Leaderboard::addPlayerEntries(const DynamicArray<Player>& players) {
    for (int i = 0; i < players.getSize(); ++i) {
        addPlayerEntry(players.at(i));
    }
}
// Helper function for sorting leaderboard
void Leaderboard::sortLeaderboardHelper(LeaderboardNode*& head, bool ascending) {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    LeaderboardNode* ptr1;
    LeaderboardNode* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ascending ? (ptr1->player.getScore() > ptr1->next->player.getScore())
                : (ptr1->player.getScore() < ptr1->next->player.getScore())) {
                std::swap(ptr1->player, ptr1->next->player);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Sort the leaderboard by highest score
void Leaderboard::sortLeaderboard() {
    sortLeaderboardHelper(head, false);
}

// Sort the leaderboard by lowest score
void Leaderboard::sortLeaderboardByLowestScore() {
    sortLeaderboardHelper(head, true);
}



void Leaderboard::displayLeaderboardHelper(LeaderboardNode* node) const {
    if (node != nullptr) {
        const Player& player = node->player;
        std::cout << std::left << std::setw(20) << player.getName()
            << std::setw(10) << player.getQuestionID1() << std::setw(10) << player.getScore1()
            << std::setw(10) << player.getQuestionID2() << std::setw(10) << player.getScore2()
            << std::setw(10) << player.getQuestionID3() << std::setw(10) << player.getScore3()
            << std::setw(15) << player.getScore() << std::endl;
        displayLeaderboardHelper(node->next);
    }
}

void Leaderboard::displayLeaderboard() const {
    // Print table header
    std::cout << std::left << std::setw(20) << "Player"
        << std::setw(10) << "Q1" << std::setw(10) << "Score1"
        << std::setw(10) << "Q2" << std::setw(10) << "Score2"
        << std::setw(10) << "Q3" << std::setw(10) << "Score3"
        << std::setw(15) << "Total Score" << std::endl;
    std::cout << std::string(95, '-') << std::endl;

    displayLeaderboardHelper(head);
}


LeaderboardNode* Leaderboard::searchPlayerHelper(LeaderboardNode* node, const std::string& name) const {
    while (node != nullptr && node->player.getName() != name) {
        node = node->next;
    }
    return node;
}

LeaderboardNode* Leaderboard::searchPlayer(const std::string& name) const {
    return searchPlayerHelper(head, name);
}