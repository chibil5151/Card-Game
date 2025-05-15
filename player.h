#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <string>
//#include "DynamicArray.h"

class AnsweredQuestionNode {
public:
    Card card;
    bool correct;
    int score;


    AnsweredQuestionNode* next;

    AnsweredQuestionNode(const Card& card, bool correct, int score)
        : card(card), correct(correct), score(score), next(nullptr) {}

};

class Player {
public:
    std::string studentID;
    std::string studentName;
    std::string questionID1;
    int score1;
    std::string questionID2;
    int score2;
    std::string questionID3;
    int score3;
    int totalScore;

    //constructor
    Player();
    Player(const std::string& sID, const std::string& sName, const std::string& qID1, int s1,
        const std::string& qID2, int s2, const std::string& qID3, int s3, int tScore);
    Player(const std::string& sName);

    std::string answerQuestion(const Card& card);
    void updateScore(int score);
    void addAnsweredQuestion(const Card& card, bool correct, int score);
    void printAnsweredQuestions() const;
    int getNumberOfAnsweredQuestions() const;
    void setStudentID(const std::string& newID); 

    //getter
    std::string getStudentID() const;
    std::string getName() const;
    std::string getQuestionID1() const;
    int getScore1() const;
    std::string getQuestionID2() const;
    int getScore2() const;
    std::string getQuestionID3() const;
    int getScore3() const;
    int getScore() const;
    AnsweredQuestionNode* getAnsweredQuestionsHead() const;

private:
    AnsweredQuestionNode* answeredQuestionsHead;
};

#endif
