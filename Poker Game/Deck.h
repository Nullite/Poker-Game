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
	void getStraight()
	{
		deck.at(1) = deck.at(4);
		deck.at(2) = deck.at(9);
		deck.at(3) = deck.at(12);
		deck.at(4) = deck.at(16);
	}
	void getFullHouse()
	{
		deck.at(3) = deck.at(12);
		deck.at(4) = deck.at(13);

	}
	void getStraitFlush()
	{
		deck.at(1) = deck.at(4);
		deck.at(2) = deck.at(8);
		deck.at(3) = deck.at(12);
		deck.at(4) = deck.at(16);
		deck.at(5) = deck.at(41);
		deck.at(6) = deck.at(19);
	}
	void getWheel()
	{
		deck.at(0) = deck.at(51);
		deck.at(2) = deck.at(6);
		deck.at(3) = deck.at(10);
		deck.at(6) = deck.at(12);
	}
	void getSet()
	{
		deck.at(3) = deck.at(34);
		deck.at(4) = deck.at(26);
		deck.at(5) = deck.at(41);
		deck.at(6) = deck.at(17);
	}
	void getTwoPairs()
	{
		deck.at(1) = deck.at(12);
		deck.at(4) = deck.at(13);
		deck.at(0) = deck.at(24);
		deck.at(6) = deck.at(49);
	}
};

