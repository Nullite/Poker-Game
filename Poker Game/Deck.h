#pragma once
#include <Windows.h>
#include <random>
#include <algorithm>
#include "Card.h"
class Deck
{
	std::vector<Card*> deck;
	int cardPointer;

public:
	Deck();
	Card getCard();
	void shuffle();
	void endRound();
};

