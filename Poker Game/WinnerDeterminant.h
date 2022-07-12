#pragma once
#include "Interface.h"
class WinnerDeterminant
{
	enum {highCard, pair, twoPairs, set, straight, flush, fullHouse, forOfTheKind, straightFlush, royalFlush};
	std::vector<Card> playerCards;
	std::vector<Card> croupierCards;
	std::vector<Card> tableCards;
	std::vector<Card> sharedPlayerCards;
	std::vector<Card> sharedCroupierCards;
	short playerCobinationID;
	short croupierCombinationID;

	void fillSharedCards(CardHolder& cardHolder);

	bool checkIfTwoPairs(CardHolder& cardHolder);
	bool checkIfPair(CardHolder& cardHolder);
	
public:
	WinnerDeterminant(CardHolder& player, CardHolder& croupier, CardHolder& table);
	WinnerDeterminant(CardHolder& player, CardHolder& table);
	
};

