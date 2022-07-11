#include "Deck.h"

Deck::Deck()
{
	cardPointer = 0;
	for (size_t i{ 0 }; i < 52; i++)
	{
		Card* card = new Card;
		deck.push_back(card);
	}
}

Card Deck::getCard()
{
	if (cardPointer > 51) throw "deck is over";
	Card temp = *deck.at(cardPointer);
	cardPointer++;
	return temp;
}

void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(deck.begin(), deck.end(), g);
}

void Deck::endRound()
{
	cardPointer = 0;
	shuffle();
}
