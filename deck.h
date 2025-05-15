#pragma once
#ifndef DECK_H
#define DECK_H

#include "card.h"

// Base class for decks
class CardDeck {
public:
    virtual void addCard(const Card& card) = 0;
    virtual Card removeCard() = 0;
};

// Linked list node for UnansweredDeck
class CardNode {
public:
    Card card;
    CardNode* next;
    CardNode(const Card& card) : card(card), next(nullptr) {}
};

// UnansweredDeck using linked list
class UnansweredDeck : public CardDeck {
public:
    UnansweredDeck();
    ~UnansweredDeck();
    bool isEmpty() const;
    void addCard(const Card& card) override;
    Card removeCard() override;
    Card getNextCard();
    void shuffleDeck();
    //void loadFromFile(const std::string& filename);
private:
    CardNode* head;
};


// Stack for AnsweredDeck
class CardStack {
public:
    CardStack();
    ~CardStack();
    void push(const Card& card);
    Card pop();
    bool isEmpty() const;
private:
    struct StackNode {
        Card card;
        StackNode* next;
        StackNode(const Card& card) : card(card), next(nullptr) {}
    };
    StackNode* top;
};

// AnsweredDeck using stack
class AnsweredDeck : public CardDeck {
public:
    void addCard(const Card& card) override;
    Card removeCard() override;
private:
    CardStack stack;
};


// Queue for DiscardedDeck
class CardQueue {
public:
    CardQueue();
    ~CardQueue();
    void enqueue(const Card& card);
    Card dequeue();
    bool isEmpty() const;
    const Card& peekFront() const;

private:
    struct QueueNode {
        Card card;
        QueueNode* next;
        QueueNode(const Card& card);
    };
    QueueNode* front;
    QueueNode* back;
};

// DiscardedDeck using queue
class DiscardedDeck : public CardDeck {
public:
    bool isEmpty() const;
    void addCard(const Card& card) override;
    Card removeCard() override;
    const Card& peekCard() const;
private:
    CardQueue queue;
};

#endif
