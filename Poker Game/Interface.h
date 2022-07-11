#pragma once
#include "Deck.h"
#include "CardHolder.h"
#include "Card.h"
class Interface
{
	COORD getCursor();
	void setCursor(COORD coord);
public:
	void showCards(CardHolder& player, bool isFace);
	void endRound(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table);
};

