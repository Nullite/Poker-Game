#include "WinnerDeterminant.h"

WinnerDeterminant::WinnerDeterminant(CardHolder& player, CardHolder& croupier, CardHolder& table)
{
	playerCards= player.getCards();
	croupierCards = croupier.getCards();
	tableCards = table.getCards();
	playerCobinationID = 0;
	croupierCombinationID = 0;
}

WinnerDeterminant::WinnerDeterminant(CardHolder& player, CardHolder& table)
{
	if (player.getID() != 1 || table.getID() != 3) throw "first parametr must be player, second parametr must be table!";

	playerCards = player.getCards();
	tableCards = table.getCards();
	playerCobinationID = 0;
	croupierCombinationID = 0;
}

void WinnerDeterminant::fillSharedCards(CardHolder& cardHolder)
{
	short ID = cardHolder.getID();
	if (ID < 1 || ID > 2) throw "only player and croupier have combinations";
	if (ID == 2 && !croupierCards.size()) throw "threre is no croupier added";

	if (ID == 1)
	{
		if (sharedPlayerCards.size()) sharedPlayerCards.clear();
		for (Card card : tableCards)
		{
			sharedPlayerCards.push_back(card);
		}
		for (Card card : playerCards)
		{
			{
				sharedPlayerCards.push_back(card);
			}
		}
	}
	else
	{
		if (sharedCroupierCards.size()) sharedCroupierCards.clear();
		for (Card card : tableCards)
		{
			sharedPlayerCards.push_back(card);
		}
		for (Card card : croupierCards)
		{
			sharedCroupierCards.push_back(card);
		}
	}
}

bool WinnerDeterminant::checkIfPair(CardHolder& cardHolder)
{
	fillSharedCards(cardHolder);
	short ID = cardHolder.getID();

	size_t size = ID == 1 ? sharedPlayerCards.size() : sharedCroupierCards.size();
	for (size_t i{ 0 }; i < size - 1; ++i)
	{
		std::string checkValue = ID == 1 ? sharedPlayerCards.at(i).getBlanck().value : sharedCroupierCards.at(i).getBlanck().value;
		for (size_t j{ i + 1 }; j < size; ++j)
		{
			std::string compare = ID == 1 ? sharedPlayerCards.at(j).getBlanck().value : sharedCroupierCards.at(j).getBlanck().value;
			if (checkValue == compare) return true;
		}
	}
	return false;
}

bool WinnerDeterminant::checkIfTwoPairs(CardHolder& cardHolder)
{
	fillSharedCards(cardHolder);
	short ID = cardHolder.getID();

	size_t size = ID == 1 ? sharedPlayerCards.size() : sharedCroupierCards.size();
	short firstCardPointer = 0;
	short secondCardPointer = 0;

	for (size_t i{ 0 }; i < size - 1; ++i)
	{
		std::string checkValue = ID == 1 ? sharedPlayerCards.at(i).getBlanck().value : sharedCroupierCards.at(i).getBlanck().value;
		firstCardPointer = i;
		for (size_t j{ i + 1 }; j < size; ++j)
		{
			std::string compare = ID == 1 ? sharedPlayerCards.at(j).getBlanck().value : sharedCroupierCards.at(j).getBlanck().value;
			if (checkValue == compare)
			{
				secondCardPointer = j;
				break;
			}
		}
		if (secondCardPointer) break;
	}

	if (!secondCardPointer) return false;

	switch (ID)
	{
	case 1:
		sharedPlayerCards.erase(sharedPlayerCards.begin() + firstCardPointer);
		sharedPlayerCards.erase(sharedPlayerCards.begin() + --secondCardPointer);
		break;
	case 2:
		sharedCroupierCards.erase(sharedCroupierCards.begin() + firstCardPointer);
		sharedCroupierCards.erase(sharedCroupierCards.begin() + --secondCardPointer);
		break;
	}

	size = ID == 1 ? sharedPlayerCards.size() : sharedCroupierCards.size();
	for (size_t i{ 0 }; i < size - 1; ++i)
	{
		std::string checkValue = ID == 1 ? sharedPlayerCards.at(i).getBlanck().value : sharedCroupierCards.at(i).getBlanck().value;
		for (size_t j{ i + 1 }; j < size; ++j)
		{
			std::string compare = ID == 1 ? sharedPlayerCards.at(j).getBlanck().value : sharedCroupierCards.at(j).getBlanck().value;
			if (checkValue == compare) return true;
		}
	}
	return false;
}
