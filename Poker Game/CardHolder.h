#pragma once
#include "Deck.h"

class CardHolder
{
protected:
	short ID;
	std::vector<Card> cards;
	virtual void setID() = 0;
public:
	virtual void takeCards(Deck& deck);
	std::vector<Card> getCards();
	int getID();
	virtual void endRound();
};

class Player : public CardHolder
{
	void setID() override;

public:
	Player();
};

class Croupier : public CardHolder
{
	void setID() override;

public:
	Croupier();
};

class Table : public CardHolder
{
	void setID() override;
	short roundCount;

public:
	Table();
	void takeCards(Deck& deck) override;
	void endRound() override;
};

