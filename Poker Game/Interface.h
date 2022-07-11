#pragma once
#include "Deck.h"
#include "CardHolder.h"
#include "Card.h"
class Interface
{
	std::string chipsPlaceHolder;
	COORD getCursor();
	void setCursor(COORD coord);
public:
	Interface();
	void showCards(CardHolder& cardHolder, bool isFace);
	void endRound(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table);
	void showChips(CardHolder& cardholder);
	void showChipsPlaceHolders();
};

