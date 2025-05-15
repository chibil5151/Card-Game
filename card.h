#pragma once
#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    Card(); // Default constructor
    //Card(const std::string& question, const std::string& answer, int score);
    Card(const std::string& questionID, const std::string& format, const std::string& difficulty, const std::string& topic,
        const std::string& question, const std::string& choices, const std::string& answer, int score);

    std::string getQuestion() const;
    std::string getAnswer() const;
    int getScore() const;

    std::string getId() const;
    std::string getFormat() const;
    std::string getDifficulty() const;
    std::string getTopic() const;
    std::string getChoices() const;


private:
    /*std::string question;
    std::string answer;
    int score;*/

    std::string questionID;
    std::string format;
    std::string difficulty;
    std::string topic;
    std::string question;
    std::string choices;
    std::string answer;
    int score;
};

#endif
