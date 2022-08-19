#include <conio.h>
#include <Windows.h>
#include <random>
#include <algorithm>
#include "Card.h"
#pragma once

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

