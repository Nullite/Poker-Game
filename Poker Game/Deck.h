#pragma once
#include <conio.h>
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
	void check()
	{
		deck.at(0) = deck.at(8);
		deck.at(1) = deck.at(32);
		deck.at(5) = deck.at(29);
		deck.at(3) = deck.at(27);
		deck.at(4) = deck.at(20);
		deck.at(6) = deck.at(25);
		deck.at(7) = deck.at(19);
		//-----------------------//
		/*deck.at(0) = deck.at(20);
		deck.at(1) = deck.at(16);
		deck.at(8) = deck.at(6);
		deck.at(4) = deck.at(25);
		deck.at(5) = deck.at(29);
		deck.at(6) = deck.at(39);
		deck.at(7) = deck.at(13);*/
		//-----------------------//
		/*deck.at(0) = deck.at(9);
		deck.at(1) = deck.at(28);
		deck.at(4) = deck.at(20);
		deck.at(5) = deck.at(22);
		deck.at(6) = deck.at(18);
		deck.at(7) = deck.at(12);
		deck.at(8) = deck.at(42);*/
	}
};

