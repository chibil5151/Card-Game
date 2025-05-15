#include "user_interface.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip> 

using namespace std;

bool UserInterface::showInstructions() {
    std::cout << "\t\tGAME INSTRUCTIONS:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::cout << "1. The game will have 3 rounds.\n";
    std::cout << "2. In each round, a question can be chosen to be answered by the player.\n";
    std::cout << "3. Players will have a limited time to answer the question.\n";
    std::cout << "4. Correct answers will earn points, and incorrect answers will deduct points.\n";
    std::cout << "5. The player with the highest score at the end of the game wins.\n";
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "\n";

    char choice;
    while (true) {
        std::cout << "Would you like to start the game? (y/n): ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            std::cout << "You chose to continue, so let's start!" << std::endl;
            std::cout << "\n" << std::endl;
            return true;
        }
        else if (choice == 'n' || choice == 'N') {
            std::cout << "You chose to stop, bye!" << std::endl;
            std::cout << "\n" << std::endl;

            return false;
        }
        else {
            std::cout << "Invalid choice. Please enter 'y' or 'n'." << std::endl;
        }
    }
}

std::string UserInterface::getPlayerName() {
    std::string name;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "\tWELCOME TO CARD TRIVIA GAME!\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Please enter the player's name to start." << std::endl;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "\nHi " << name << "! Please take a look at the instructions below." << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    return name;
}



std::string UserInterface::getPlayerAnswer(const std::string& playerName, const Card& card) {
    std::string answer;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Your Answer: ";

    std::cin >> answer;
        
    return answer;
}

void UserInterface::displayLeaderboard(const Leaderboard& leaderboard) {
    std::cout << "Leaderboard:\n";
    leaderboard.displayLeaderboard();
}
int UserInterface::chooseDeck(const DiscardedDeck& discardedDeck) {
    int choice;
    while (true) {
        std::cout << "Choose a deck to draw a card from:\n";
        std::cout << "1. Unanswered Deck\n";
        std::cout << "2. Discarded Deck (80% of the mark of the question score):\n";
        if (!discardedDeck.isEmpty()) {
            std::cout << "\tQuestion on top of the Discarded Deck:\n";
            std::cout << "\t" << discardedDeck.peekCard().getQuestion() << "\n";
        }
        std::cout << std::string(50, '-') << std::endl;

        while (true) {
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> choice;
            if (std::cin.fail() || (choice != 1 && choice != 2)) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                std::cout << "Invalid choice. Please enter 1 or 2.\n";
            }
            else {
                return choice; // valid choice
            }
        }
    }
    return choice;
}

void UserInterface::deckEmptyMessage(const std::string& deckName) {
    std::cout << "The " << deckName << " Deck is empty. Please choose the other deck.\n";
}

void UserInterface::invalidChoiceMessage() {
    std::cout << "Invalid choice. Please enter 1 or 2.\n";
}

bool UserInterface::askToAnswerQuestion(const Card& card) {
    char choice;
    while (true) {
        std::cout << "Do you want to answer? (y/n): ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else {
            std::cout << "Invalid choice. Please enter 'y' or 'n'." << std::endl;
        }
    }
}

void UserInterface::showQuestionDetails(const Card& card) {
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Question ID: " << card.getId() << "\n";
    std::cout << "Format: " << card.getFormat() << "\n";
    std::cout << "Difficulty: " << card.getDifficulty() << "\n";
    std::cout << "Score: " << card.getScore() << "\n";
    std::cout << "Topic: " << card.getTopic() << "\n";
    std::cout << "\nQuestion:\n" << card.getQuestion() << "\n\n";

    // Check if the format is "True/False"
    if (card.getFormat() == "TrueFalse") {
        std::cout << "Choices:\n";
        std::cout << "1. True\n";
        std::cout << "2. False\n";
    }
    else if (card.getFormat() == "FillinTheBlank") {

    }else if (card.getFormat() == "MultipleCorrect") {

        std::cout << "Choices:\n";
        std::istringstream choicesStream(card.getChoices());
        std::string choice;
        while (std::getline(choicesStream, choice, ';')) {
            std::cout << choice << "\n";
        }
        std::cout << "Please seprate your answer by a semicolon(;).\n";
    }
    else {
        // Split choices by semicolon and display each choice on a new line
        std::cout << "Choices:\n";
        std::istringstream choicesStream(card.getChoices());
        std::string choice;
        while (std::getline(choicesStream, choice, ';')) {
            std::cout << choice << "\n";
        }
    }
    std::cout << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
}

    
void UserInterface::displayEndGameMenu(const DynamicArray<Player>& players, Leaderboard& leaderboard, const WinnersChart& winnersChart) {

    const int width = 50;  // Width of the menu
    const std::string menuTitle = "End Game Menu";
    int padding = (width - menuTitle.size()) / 2;

    while (true) {
        std::cout << std::string(width, '=') << std::endl;
        std::cout << std::string(padding, ' ') << menuTitle << std::endl;
        std::cout << std::string(width, '=') << std::endl;
        std::cout << "1. Display Leaderboard Menu" << std::endl;
        std::cout << "2. Display Winner Chart Menu" << std::endl;
        std::cout << "3. Save & Exit" << std::endl;
        std::cout << "4. Exit without Saving" << std::endl;
        std::cout << string(50, '-') << endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            // Call the method to display the leaderboard
            UserInterface::displayLeaderboardMenu(leaderboard);
            break;
        case 2:
            // Call the method to display the winner chart
            UserInterface::displayWinnersChartMenu(winnersChart);
            break;
        case 3:
            // Save game data and exit
            FileIO::savePlayersToScoresFile(players);
            std::cout << "Game saved successfully. Exiting..." << std::endl;
            exit(0);
            break;
        case 4:
            // Exit without saving
            std::cout << "Exiting without saving..." << std::endl;
            exit(0);
            break;

        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}

void UserInterface::displayWinnersChartMenu(const WinnersChart& winnersChart) {
    const int width = 50;  // Width of the menu
    const std::string menuTitle = "Winners Chart Menu";
    int padding = (width - menuTitle.size()) / 2;

    while (true) {
        std::cout << std::string(width, '=') << std::endl;
        std::cout << std::string(padding, ' ') << menuTitle << std::endl;
        std::cout << std::string(width, '=') << std::endl;
        std::cout << "1. Show Winner Chart" << std::endl;
        std::cout << "2. Search Winner Chart" << std::endl;
        std::cout << "3. Back to End Game Menu" << std::endl;
        std::cout << std::string(width, '-') << std::endl;
        std::cout << "Enter your choice: ";
        

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            // Call the method to display the winner chart
            winnersChart.displayTopWinners(30); // Display top 30 winners
            break;
        case 2:
            // Call the method to search the winner chart
            UserInterface::searchWinnerChart(winnersChart);
            break;
        case 3:
            // Back to End Game Menu
            return;
        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}

void UserInterface::searchWinnerChart(const WinnersChart& winnersChart) {
    std::string playerName;
    std::cout << "Enter player name to search: ";
    std::cin >> playerName;

    int rank = winnersChart.getPlayerRank(playerName);
    if (rank != -1) {
        std::cout << std::string(50, '-') << std::endl;
        std::cout <<"Search Result:" << std::endl;
        std::cout << playerName << " is ranked " << rank << " !" << std::endl;
    }
    else {
        std::cout << playerName << " is not in the top 30 winners." << std::endl;
    }
}



//void UserInterface::displayLeaderboardMenu(const Leaderboard& leaderboard) {
void UserInterface::displayLeaderboardMenu(Leaderboard & leaderboard) {

    const int width = 50;
    const std::string menuTitle = "Leaderboard Menu";
    int padding = (width - menuTitle.size()) / 2;

    while (true) {
        std::cout << std::string(width, '=') << std::endl;
        std::cout << std::string(padding, ' ') << menuTitle << std::endl;
        std::cout << std::string(width, '=') << std::endl;
        std::cout << "1. Show Leaderboard" << std::endl;
        std::cout << "2. Search Leaderboard" << std::endl;
        std::cout << "3. Sort Leaderboard" << std::endl;
        //std::cout << "4. Show Scores by Topic" << std::endl; // New option
        std::cout << "4. Back to End Game Menu" << std::endl;
        std::cout << std::string(width, '-') << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            leaderboard.displayLeaderboard();
            break;
        case 2:
            UserInterface::searchLeaderboard(leaderboard);
            break;
        case 3:
            UserInterface::displaySortingMenu(leaderboard);
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}

void UserInterface::searchLeaderboard(const Leaderboard& leaderboard) {
    std::string playerName;
    std::cout << "Enter player name to search: ";
    std::cin >> playerName;

    LeaderboardNode* playerNode = leaderboard.searchPlayer(playerName);
    if (playerNode != nullptr) {
        const Player& player = playerNode->player;
        std::cout << string(50, '-') << endl;
        std::cout << "Player: " << player.getName() << " - Total Score: " << player.getScore() << std::endl;
        AnsweredQuestionNode* current = player.getAnsweredQuestionsHead();
        while (current != nullptr) {
            std::cout << "\tQuestion ID: " << current->card.getId()
                << " - Score: " << current->score
                << " - Correct: " << (current->correct ? "Yes" : "No") << std::endl;
            current = current->next;
        }
    }
    else {
        std::cout << "Player not found in the leaderboard." << std::endl;
    }
}

void UserInterface::displaySortingMenu(Leaderboard& leaderboard) {
    int choice;
    std::string topic;
    std::cout << string(50, '-') << endl;
    std::cout << "Choose sorting option:\n";
    std::cout << "1. Sort by highest score\n";
    std::cout << "2. Sort by lowest score\n";
    std::cout << string(50, '-') << endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        leaderboard.sortLeaderboard();
        leaderboard.displayLeaderboard();
        break;
    case 2:
        leaderboard.sortLeaderboardByLowestScore();
        leaderboard.displayLeaderboard();
        break;
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}

