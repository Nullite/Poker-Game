#pragma once
#include "Deck.h"

class CardHolder
{
protected:
	short chips;
	short ID;
	std::vector<Card> cards;
	virtual void setID() = 0;
public:
	virtual void takeCards(Deck& deck);
	std::vector<Card> getCards();
	int getID();
	virtual void setChips() = 0;
	void winChips(short bank);
	virtual void endRound();
	short getChips();
	void bet(short bet);
};

class Player : public CardHolder
{
	void setID() override;
public:
	Player();
	void setChips() override;
};

class Croupier : public CardHolder
{
	void setID() override;
public:
	Croupier();
	void setChips() override;
};

class Table : public CardHolder
{
	void setID() override;
	short roundCount;

public:
	Table();
	void takeCards(Deck& deck) override;
	void endRound() override;
	void setChips() override;
};
