#include "game_manager.h"
#include <iostream>
#include <sstream>
#include <iomanip>


GameManager::GameManager() {

    FileIO::loadPlayersnDeck(players, answeredDeck, unansweredDeck, discardedDeck);
    setupPlayers();
    
}

void GameManager::setupPlayers() {
    std::string playerName = UserInterface::getPlayerName();
    player = Player(playerName);
}

void GameManager::startGame() {
    const int width = 50;

    if (UserInterface::showInstructions() == true) {
        for (int round = 1; round <= 3; ++round) {
            std::cout << std::string(width, '=') << std::endl;

            // Center the round text
            std::string roundText = "ROUND " + std::to_string(round);
            int padding = (width - roundText.size()) / 2;
            std::cout << std::string(padding, ' ') << roundText << std::endl;
            std::cout << std::string(width, '=') << std::endl;

            playRound(round); 
        }
        endGame();
    }
    else {
        exit(0);
    }
}

void GameManager::playRound(int i) {
    while (true) {
        // Ask the user to choose a deck
        int choice = UserInterface::chooseDeck(discardedDeck);
        Card card;
        if (choice == 1) {
            // If the user chooses the unanswered deck
            if (!unansweredDeck.isEmpty()) {
                card = unansweredDeck.getNextCard();
            }
            else {
                UserInterface::deckEmptyMessage("Unanswered");
                continue;
            }
        }
        else if (choice == 2) {
            //If the user chooses the discarded deck
            if (!discardedDeck.isEmpty()) {
                card = discardedDeck.peekCard();
                
            }
            else {
                UserInterface::invalidChoiceMessage();
                continue;
            }
        }
        // Show question details
        UserInterface::showQuestionDetails(card);

        // Ask if the player wants to answer the question
        bool choiceToAnswer = UserInterface::askToAnswerQuestion(card);
        if (!choiceToAnswer) {
            // If the player chooses not to answer, put the card at the bottom of the discarded deck if it was chosen from there
            if (choice == 2) {
                discardedDeck.addCard(discardedDeck.removeCard());
            }
            else {
                discardedDeck.addCard(card); // Discard the card to the end
            }
            break; // Move to the next round
        }

        // Get the player's answer and check if it's correct
        std::string answer = player.answerQuestion(card);
        bool correct = (answer == card.getAnswer());
        int score = 0;

        if (card.getFormat() == "MultipleCorrect") {
            // Handle "MultipleCorrect" format
            int totalCorrect = 0;
            int correctCount = 0;

            std::istringstream correctAnswersStream(card.getAnswer());
            std::istringstream playerAnswersStream(answer);
            std::string correctAnswer, playerAnswer;

            // Count total correct answers
            while (std::getline(correctAnswersStream, correctAnswer, ';')) {
                totalCorrect++;
            }

            // Count correct answers in player's answer
            while (std::getline(playerAnswersStream, playerAnswer, ';')) {
                correctAnswersStream.clear();
                correctAnswersStream.str(card.getAnswer());
                while (std::getline(correctAnswersStream, correctAnswer, ';')) {
                    if (playerAnswer == correctAnswer) {
                        correctCount++;
                        break;
                    }
                }
            }

            // Determine the score based on correctness
            if (correctCount == totalCorrect) {
                correct = true;
                score = card.getScore();
            }
            else if (correctCount > 0) {
                score = card.getScore() / 2;
            }
        }
        else {
            // Handle other formats
            correct = (answer == card.getAnswer());
            score = correct ? card.getScore() : 0;
        }

        if (choice == 2) {
            score = static_cast<int>(score * 0.8); // 80% of the original score for discarded deck
            discardedDeck.removeCard(); // Remove the card from the discarded deck
        }
        else {
            unansweredDeck.removeCard(); // Remove the card from the unanswered deck
        }
        switch (i)
        {
        case 1:
            player.questionID1 = card.getId();
            player.score1 = score;
            break;
        case 2:
            player.questionID2 = card.getId();
            player.score2 = score;
            break;
        case 3:
            player.questionID3 = card.getId();
            player.score3 = score;
            break;
        default:

            break;
        }
        player.addAnsweredQuestion(card, correct, score);
        player.updateScore(score);
        answeredDeck.addCard(card); // Place answered card at the top
        break;

    }

}

void GameManager::endGame(){
    player.setStudentID("ST0" + std::to_string(players.getSize() + 1));
    players.push_back(player);
    leaderboard.addPlayerEntries(players);
    winnersChart.addPlayers(players);


    leaderboard.sortLeaderboard();
    player.printAnsweredQuestions();

    UserInterface::displayEndGameMenu(players, leaderboard, winnersChart);

}

GameManager::~GameManager() {
    // No need to delete players, DynamicArray handles its own memory management
}

    