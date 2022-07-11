#pragma once
#include "Deck.h"
#include "CardHolder.h"
#include "Card.h"
class Interface
{
	std::string chipsPlaceHolder;
	std::string actionPlaceHolder;
	COORD getCursor();
	void setCursor(COORD coord);
	std::string getLineTodisplay(size_t& from, std::string _where);
	bool checkIfRedSuit(std::string card);
public:
	Interface();
	void showCards(CardHolder& cardHolder, bool isFace);
	void endRound(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table);
	void showChips(CardHolder& cardholder);
	void showChipsPlaceHolders();
	void showActionPlaceHolder();
};

