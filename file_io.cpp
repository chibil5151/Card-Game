#include "file_io.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> // For std::random_shuffle
#include <ctime>     // For std::time
#include <iomanip>

// Helper function to trim whitespace
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to load questions into a DynamicArray for quick lookup
void loadQuestionsToArray(DynamicArray<Card>& questionArray) {
    std::ifstream file("questions.csv");
    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string questionIDStr, format, difficulty, topic, question, choices, answer, scoreStr;

        std::getline(ss, questionIDStr, ',');
        std::getline(ss, format, ',');
        std::getline(ss, difficulty, ',');
        std::getline(ss, topic, ',');
        std::getline(ss, question, ',');
        std::getline(ss, choices, ',');
        std::getline(ss, answer, ',');
        std::getline(ss, scoreStr, ',');

        // Trim whitespace
        questionIDStr = trim(questionIDStr);
        format = trim(format);
        difficulty = trim(difficulty);
        topic = trim(topic);
        question = trim(question);
        choices = trim(choices);
        answer = trim(answer);
        scoreStr = trim(scoreStr);

        try {
            int score = std::stoi(scoreStr);

            Card card(questionIDStr, format, difficulty, topic, question, choices, answer, score);
            questionArray.push_back(card);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << " for scoreStr: " << scoreStr << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << " for scoreStr: " << scoreStr << std::endl;
        }
    }
}


void FileIO::loadPlayersnDeck(DynamicArray<Player>& players, AnsweredDeck& answeredDeck, UnansweredDeck& unansweredDeck, DiscardedDeck& discardedDeck) {
    std::ifstream file("score.csv");
    std::string line;

    // DynamicArray to store answered question IDs
    DynamicArray<std::string> answeredQuestionIDs;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string studentID, studentName, questionID1, scoreStr1, questionID2, scoreStr2, questionID3, scoreStr3, totalScoreStr;

        std::getline(ss, studentID, ',');
        std::getline(ss, studentName, ',');
        std::getline(ss, questionID1, ',');
        std::getline(ss, scoreStr1, ',');
        std::getline(ss, questionID2, ',');
        std::getline(ss, scoreStr2, ',');
        std::getline(ss, questionID3, ',');
        std::getline(ss, scoreStr3, ',');
        std::getline(ss, totalScoreStr, ',');

        int score1 = std::stoi(scoreStr1);
        int score2 = std::stoi(scoreStr2);
        int score3 = std::stoi(scoreStr3);
        int totalScore = std::stoi(totalScoreStr);

        Player player(studentID, studentName, questionID1, score1, questionID2, score2, questionID3, score3, totalScore);
        players.push_back(player);

        answeredQuestionIDs.push_back(questionID1);
        answeredQuestionIDs.push_back(questionID2);
        answeredQuestionIDs.push_back(questionID3);
    }

    // Load questions into a DynamicArray for lookup
    DynamicArray<Card> questionArray;
    loadQuestionsToArray(questionArray);

    // Shuffle the question array
    std::srand(static_cast<unsigned int>(std::time(0))); // Cast to unsigned int
    std::random_shuffle(&questionArray[0], &questionArray[0] + questionArray.getSize());


    // Populate the decks
    for (int i = 10; i < questionArray.getSize(); ++i) {
        Card card = questionArray[i];
        bool isAnswered = false;
        for (int j = 0; j < answeredQuestionIDs.getSize(); ++j) {
            if (card.getId() == answeredQuestionIDs[j]) {
                answeredDeck.addCard(card);
                isAnswered = true;
                break;
            }
        }
        if (!isAnswered) {
            // Move the first 10 cards to the DiscardedDeck
            for (int i = 0; i < 10 && i < questionArray.getSize(); ++i) {
                discardedDeck.addCard(questionArray[i]);
            }
            unansweredDeck.addCard(card);
        }
    }
    // Add answered questions to players
    for (int i = 0; i < players.getSize(); ++i) {
        Player& player = players.at(i);
        for (int j = 0; j < questionArray.getSize(); ++j) {
            const Card& card = questionArray.at(j);
            if (card.getId() == player.getQuestionID1()) {
                player.addAnsweredQuestion(card, true, player.getScore1());
            }
            else if (card.getId() == player.getQuestionID2()) {
                player.addAnsweredQuestion(card, true, player.getScore2());
            }
            else if (card.getId() == player.getQuestionID3()) {
                player.addAnsweredQuestion(card, true, player.getScore3());
            }
        }
    }
}



void FileIO::savePlayersToScoresFile(const DynamicArray<Player>& players) {
    std::ofstream file("score.csv");

    // Write the header line
    file << "studentID,studentName,questionID1,score1,questionID2,score2,questionID3,score3,totalScore\n";

    // Write each player's data
    for (int i = 0; i < players.getSize(); ++i) {
        const Player& player = players.at(i);
        file << player.getStudentID() << ","
            << player.getName() << ","
            << player.getQuestionID1() << ","
            << player.getScore1() << ","
            << player.getQuestionID2() << ","
            << player.getScore2() << ","
            << player.getQuestionID3() << ","
            << player.getScore3() << ","
            << player.getScore() << "\n";
    }
}


