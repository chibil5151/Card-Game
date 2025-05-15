#pragma once
#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include "deck.h"
#include "player.h"
#include "DynamicArray.h"

class FileIO {
public:
    static void loadPlayersnDeck(DynamicArray<Player>& players, AnsweredDeck& answeredDeck, UnansweredDeck& unansweredDeck, DiscardedDeck& discardedDeck);
    static void savePlayersToScoresFile(const DynamicArray<Player>& players);
};

#endif
