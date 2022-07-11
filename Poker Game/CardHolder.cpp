#include "CardHolder.h"

void CardHolder::takeCards(Deck& deck)
{
	for (size_t i{ 0 }; i < 2; ++i)
	{
		Card card = deck.getCard();
		cards.push_back(card);
	}
}

std::vector<Card> CardHolder::getCards()
{
	return cards;
}

int CardHolder::getID()
{
	return ID;
}

void CardHolder::endRound()
{
	cards.clear();
}

short CardHolder::getChips()
{
	return chips;
}

void CardHolder::bet(short bet)
{
	chips -= bet;
}

void Player::setID()
{
	ID = 1;
}

void Player::setChips()
{
	chips = 1000;
}

Player::Player()
{
	setID();
	setChips();
}

void Croupier::setID()
{
	ID = 2;
}

void Croupier::setChips()
{
	chips = 10000;
}

Croupier::Croupier()
{
	setID();
	setChips();
}

void Table::setID()
{
	ID = 3;
}

Table::Table()
{
	setID();
	roundCount = 0;
}

void Table::takeCards(Deck& deck)
{
	roundCount++;
	if (roundCount > 3) throw "table can take cards just 3 rounds";
	if (roundCount == 1)
	{
		for (size_t i{ 0 }; i < 3; ++i)
		{
			Card card = deck.getCard();
			cards.push_back(card);
		}
	}
	else
	{
		Card card = deck.getCard();
		cards.push_back(card);
	}	
}

void Table::endRound()
{
	cards.clear();
	roundCount = 0;
}

void Table::setChips()
{
	chips = 0;
}
