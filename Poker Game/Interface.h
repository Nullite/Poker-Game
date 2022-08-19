#include "WinnerDeterminant.h"
#pragma once

class Interface
{
	bool isFold;
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
	void displayCombination(short ID, short combinationID, std::vector<Card> combination);
	std::string convertCombinationIDToString(short combinationID);
	void clearCombination(CardHolder& cardHolder);
	void displayWin(short ID);
	void clearWinDisplay();
	bool isAllIn(CardHolder& player, CardHolder& croupier);
	void showAllin(CardHolder& player, CardHolder& croupier);
	void showChipsChange(CardHolder& cardHolder, bool isBet, short change);
	void askIfRebuy(CardHolder& cardHolder);
	void underlineRebuyMenu(short menu);
	void eraseUnderlineRebuyMenu(short menu);
	bool checkIfWantToContinue(CardHolder& cardholder);
	void eraseRebuyMenu();
	void showChips(CardHolder& cardholder);
	void showChipsPlaceHolders();
	void showActionPlaceHolder();
	short selectMenuActions();
	void showCards(CardHolder& cardHolder, bool isFace);
	void showBankPlaceHolder();
	void showBank();
	void bet(short bet, CardHolder& cardHolder);
	bool action(CardHolder& player, CardHolder& croupier);
	
public:
	Interface();	
	void endRound(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table);		
	void initRound(Deck& deck, CardHolder& player, CardHolder& croupier);
	void round(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table);
	void showDown(CardHolder& croupier, CardHolder& player, CardHolder& table);
	bool checkIsPartyOver(CardHolder& player, CardHolder& croupier);
	void askContinue();
	void waitContinue();
	bool isContinue(CardHolder& player);
};

