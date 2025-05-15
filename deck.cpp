#include "deck.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

// UnansweredDeck implementation using linked list
UnansweredDeck::UnansweredDeck() : head(nullptr) {}

UnansweredDeck::~UnansweredDeck() {
    while (head) {
        CardNode* temp = head;
        head = head->next;
        delete temp;
    }
}

bool UnansweredDeck::isEmpty() const {
    return head == nullptr;
}

void UnansweredDeck::addCard(const Card& card) {
    CardNode* newNode = new CardNode(card);
    newNode->next = head;
    head = newNode;
}

Card UnansweredDeck::removeCard() {
    if (head == nullptr) {
        throw std::out_of_range("Deck is empty");
    }
    CardNode* temp = head;
    Card card = head->card;
    head = head->next;
    delete temp;
    return card;
}

Card UnansweredDeck::getNextCard() {
    return removeCard();
}

void UnansweredDeck::shuffleDeck() {
    // Shuffle the deck using any suitable algorithm
}


// Stack implementation for AnsweredDeck
CardStack::CardStack() : top(nullptr) {}

CardStack::~CardStack() {
    while (top) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}

void CardStack::push(const Card& card) {
    StackNode* newNode = new StackNode(card);
    newNode->next = top;
    top = newNode;
}

Card CardStack::pop() {
    if (top == nullptr) {
        throw std::out_of_range("Stack is empty");
    }
    StackNode* temp = top;
    Card card = top->card;
    top = top->next;
    delete temp;
    return card;
}

bool CardStack::isEmpty() const {
    return top == nullptr;
}

void AnsweredDeck::addCard(const Card& card) {
    stack.push(card);
}

Card AnsweredDeck::removeCard() {
    return stack.pop();
}

// CardQueue implementation
CardQueue::CardQueue() : front(nullptr), back(nullptr) {}

CardQueue::~CardQueue() {
    while (front) {
        QueueNode* temp = front;
        front = front->next;
        delete temp;
    }
    back = nullptr;
}

void CardQueue::enqueue(const Card& card) {
    QueueNode* newNode = new QueueNode(card);
    if (isEmpty()) {
        front = newNode;
        back = newNode;
    }
    else {
        back->next = newNode; // Add the new node to the end of the queue
        back = newNode; // Update the back pointer to the new node
    }
}

Card CardQueue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    QueueNode* frontNode = front;
    Card dequeuedCard = frontNode->card;
    front = front->next;
    if (front == nullptr) {
        back = nullptr;
    }
    delete frontNode;
    return dequeuedCard;
}

bool CardQueue::isEmpty() const {
    return front == nullptr;
}

CardQueue::QueueNode::QueueNode(const Card& card) : card(card), next(nullptr) {}

const Card& CardQueue::peekFront() const {
    if (isEmpty()) {
        throw std::out_of_range("Card queue is empty");
    }
    return front->card;
}


bool DiscardedDeck::isEmpty() const
{
    return queue.isEmpty();
}

// DiscardedDeck implementation
void DiscardedDeck::addCard(const Card& card) {
    queue.enqueue(card);
}

Card DiscardedDeck::removeCard() {
    return queue.dequeue();
}

const Card& DiscardedDeck::peekCard() const {
    return queue.peekFront();
}
