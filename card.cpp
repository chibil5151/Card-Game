#include "card.h"

//Card::Card(const std::string& question, const std::string& answer, int score)
//    : question(question), answer(answer), score(score) {}

// Default constructor
Card::Card() : questionID(""), format(""), difficulty(""), topic(""), question(""), choices(""), answer(""), score(0) {}

Card::Card(const std::string& questionID, const std::string& format, const std::string& difficulty, const std::string& topic,
    const std::string& question, const std::string& choices, const std::string& answer, int score)
    : questionID(questionID), format(format), difficulty(difficulty), topic(topic),
    question(question), choices(choices), answer(answer), score(score) {}

std::string Card::getQuestion() const {
    return question;
}

std::string Card::getAnswer() const {
    return answer;
}

int Card::getScore() const {
    return score;
}

std::string Card::getId() const { return questionID; }
std::string Card::getFormat() const { return format; }
std::string Card::getDifficulty() const { return difficulty; }
std::string Card::getTopic() const { return topic; }
std::string Card::getChoices() const { return choices; }
