#pragma once
#include <conio.h>
#include "Deck.h"
#include "CardHolder.h"
#include "Card.h"
class Interface
{
	short roundCount;
	short bank;
	std::string chipsPlaceHolder;
	std::string actionPlaceHolder;
	std::string bankPlaceHolder;
	COORD getCursor();
	void setCursor(COORD coord);
	std::string getLineTodisplay(size_t& from, std::string _where);
	bool checkIfRedSuit(std::string card);
	void underlineMenuActions(short action);
	void eraseUnderLine(short action);
	void clearTable();
public:
	Interface();
	void showCards(CardHolder& cardHolder, bool isFace);
	void endRound(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table);
	void showChips(CardHolder& cardholder);
	void showChipsPlaceHolders();
	void showActionPlaceHolder();	
	short selectMenuActions();
	void showBankPlaceHolder();
	void showBank();
	void bet(short bet, CardHolder& cardHolder);
	bool action(CardHolder& player, CardHolder& croupier);
	void initRound(Deck& deck, CardHolder& player, CardHolder& croupier);
	void round(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table);
	void showDown(CardHolder& croupier);
};

