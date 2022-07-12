#pragma once
#include "Interface.h"
class WinnerDeterminant
{
	std::vector<Card> playerCards;
	std::vector<Card> croupierCards;
	std::vector<Card> tableCards;

public:
	WinnerDeterminant(CardHolder& player, CardHolder& croupier, CardHolder& table);
};

