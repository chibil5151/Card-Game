#include "player.h"
#include "user_interface.h"
#include <iostream>
#include <sstream>

// Helper class to store strings in a linked list
class StringNode {
public:
    std::string value;
    StringNode* next;
    StringNode(const std::string& value) : value(value), next(nullptr) {}
};

// Helper function to create a linked list from a semicolon-separated string
StringNode* createListFromString(const std::string& str) {
    StringNode* head = nullptr;
    StringNode* tail = nullptr;
    std::istringstream stream(str);
    std::string item;
    while (std::getline(stream, item, ';')) {
        StringNode* newNode = new StringNode(item);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Helper function to delete a linked list
void deleteList(StringNode* head) {
    while (head) {
        StringNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Helper function to check if a player's answer contains a specific correct answer
bool containsAnswer(const std::string& playerAnswer, const std::string& correctAnswer) {
    std::istringstream playerStream(playerAnswer);
    std::string token;
    while (std::getline(playerStream, token, ';')) {
        if (token == correctAnswer) {
            return true;
        }
    }
    return false;
}


//Constructor
Player::Player() : score1(0), score2(0), score3(0), totalScore(0), answeredQuestionsHead(nullptr) {}

Player::Player(const std::string& sID, const std::string& sName, const std::string& qID1, int s1,
    const std::string& qID2, int s2, const std::string& qID3, int s3, int tScore)
    : studentID(sID), studentName(sName), questionID1(qID1), score1(s1), questionID2(qID2),
    score2(s2), questionID3(qID3), score3(s3), totalScore(tScore), answeredQuestionsHead(nullptr) {}

Player::Player(const std::string& sName)
    : studentName(sName), score1(0), score2(0), score3(0), totalScore(0), answeredQuestionsHead(nullptr) {}


// This method processes the player's answer to a question
std::string Player::answerQuestion(const Card& card) {
    // Get the player's answer
    std::string answer = UserInterface::getPlayerAnswer(studentName, card);
    return answer;
}

void Player::updateScore(int score) {
    totalScore += score;
}


void Player::addAnsweredQuestion(const Card& card, bool correct, int score) {
    AnsweredQuestionNode* newNode = new AnsweredQuestionNode(card, correct, score);
    //newNode->next = answeredQuestionsHead;
    //answeredQuestionsHead = newNode;

    if (answeredQuestionsHead == nullptr) {
        answeredQuestionsHead = newNode;
    }
    else {
        AnsweredQuestionNode* current = answeredQuestionsHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}


int Player::getNumberOfAnsweredQuestions() const {
    int count = 0;
    AnsweredQuestionNode* current = answeredQuestionsHead;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void Player::setStudentID(const std::string& newID)
{
    studentID = newID; 
}

// This method prints all the questions answered by the player along with their scores and correctness
void Player::printAnsweredQuestions() const {
    const int width = 50;
    const std::string endText = "The End";
    int padding = (width - endText.size()) / 2;

    std::cout << std::endl;
    std::cout << std::string(width, '=') << std::endl;
    std::cout << std::string(padding, ' ') << endText << std::endl;
    std::cout << std::string(width, '=') << std::endl;
    std::cout << "Player Name: " << studentName << std::endl;
    std::cout << "Total Score: " << totalScore << std::endl;
    std::cout << std::string(width, '-') << std::endl;
    std::cout << "No. of Answered Questions: " << getNumberOfAnsweredQuestions() << "\n\n";

    AnsweredQuestionNode* current = answeredQuestionsHead;
    while (current != nullptr) {
        std::cout << "Question: " << current->card.getQuestion() << std::endl;
        std::cout << "Your Answer: " << (current->correct ? "Correct" : "Incorrect") << std::endl;
        std::cout << "Correct Answer: " << current->card.getAnswer() << std::endl;
        
        std::cout << "Your Score for this Question: " << current->score << "/"<< current->card.getScore()<< std::endl; // Use the stored score

        std::cout << std::string(25, '-') << std::endl;
        current = current->next;
    }
}


std::string Player::getStudentID() const {
    return studentID;
}


std::string Player::getName() const {
    return studentName;
}

//to get the individual questions stuff
std::string Player::getQuestionID1() const {
    return questionID1;
}

int Player::getScore1() const {
    return score1;
}

std::string Player::getQuestionID2() const {
    return questionID2;
}

int Player::getScore2() const {
    return score2;
}

std::string Player::getQuestionID3() const {
    return questionID3;
}

int Player::getScore3() const {
    return score3;
}

int Player::getScore() const {
    return totalScore;
}

AnsweredQuestionNode* Player::getAnsweredQuestionsHead() const {
    return answeredQuestionsHead;
}