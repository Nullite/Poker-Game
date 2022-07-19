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

void WinnerDeterminant::combinationHandler(CardHolder& cardHolder)
{
	short ID = cardHolder.getID();
	if (ID != 1 && ID != 2) throw "only player and croupier have combinations";

	fillSharedCards(cardHolder);

	short repeatCompinationID;
	short sequenceCombinationID;
	short combinationID;

	std::vector < std::vector<Card>> repeats;
	std::vector<Card> cardsToCheck = ID == 1 ? sharedPlayerCards : sharedCroupierCards;
	std::vector<Card> sequence = getSequence(cardsToCheck);
	bool checkFlush = isFlush(cardsToCheck);
	bool checkSeqEmpty = sequence.empty();

	sequenceCombinationID = getSequenceCombinationID(sequence, checkFlush);
	if (sequenceCombinationID == straightFlush || sequenceCombinationID == royalFlush) combinationID = sequenceCombinationID;
	else
	{
		repeats = getRepeats(cardsToCheck);
		repeatCompinationID = getRepeatCombinationID(repeats);
		combinationID = repeatCompinationID > sequenceCombinationID ? repeatCompinationID : sequenceCombinationID;
	}
	fillCombinationCards(combinationID, ID, repeats, sequence);

	if (ID == 1) playerCobinationID = combinationID;
	else croupierCombinationID = combinationID;
}

short WinnerDeterminant::compareCombinations()
{
	if (playerCobinationID > croupierCombinationID) return 1;
	else if (croupierCombinationID > playerCobinationID) return 2;
	else
	{
		for (size_t i{ 0 }; i < 5; ++i)
		{
			if (playerCombination.at(i) > croupierCombination.at(i)) return 1;
			if (croupierCombination.at(i) > playerCombination.at(i)) return 2;
		}
		return 3;
	}
}

short WinnerDeterminant::getPlayerCombinationID()
{
	return playerCobinationID;
}

short WinnerDeterminant::getCroupierCombinationID()
{
	return croupierCombinationID;
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
			sharedCroupierCards.push_back(card);
		}
		for (Card card : croupierCards)
		{
			sharedCroupierCards.push_back(card);
		}
	}
}

std::vector<Card> WinnerDeterminant::getPlayerCombination()
{
	return playerCombination;
}

std::vector<Card> WinnerDeterminant::getCroupierCombination()
{
	return croupierCombination;
}

short WinnerDeterminant::getRepeatCombinationID(std::vector<std::vector<Card>>& repeats)
{
	short first;
	short second;
	short third;
	switch (repeats.size())
	{
	case 0: 
		return highCard;
	case 1:
		first = repeats.at(0).size();
		return first == 2 ? pair : first == 3 ? set : fourOfTheKind;
	case 2:
		first = repeats.at(0).size();
		second = repeats.at(1).size();
		if (first == 4 || second == 4) return fourOfTheKind;
		if (first == 3 && second == 2 || first == 2 && second == 3) return fullHouse;
		if (first == 3 && second == 3) return fullHouse;
		if (first == 2 && second == 2) return twoPairs;
		break;
	case 3:
		first = repeats.at(0).size();
		second = repeats.at(1).size();
		third = repeats.at(2).size();
		if (first == 2 && second == 2 && third == 2) return twoPairs;
		else return fullHouse;
	default:
		throw "getRepeatCombinationID argument is not correct";
	}
}

short WinnerDeterminant::getSequenceCombinationID(std::vector<Card> sequence, bool isFlush)
{
	bool isSeqEmpty = sequence.empty();
	bool checkRoyal = isSeqEmpty ? false : sequence.at(0).getBlanck().value == "A";
	if (isSeqEmpty && !isFlush) return highCard;
	if (!isSeqEmpty && !isFlush) return straight;
	if (isSeqEmpty && isFlush) return flush;
	if (!isSeqEmpty && isFlush && checkRoyal) return royalFlush;
	else return straightFlush;
}

std::vector < std::vector<Card>> WinnerDeterminant::getRepeats(std::vector<Card> cards)
{
	std::vector < std::vector<Card>> repeats;

	while (cards.size())
	{
		std::vector<Card> temp;
		std::string value = cards.at(0).getBlanck().value;
		temp.push_back(cards.at(0));
		cards.erase(cards.begin());
		for (size_t i{ 0 }; i < cards.size(); ++i)
		{
			std::string compare = cards.at(i).getBlanck().value;
			if (compare == value)
			{
				temp.push_back(cards.at(i));
				cards.erase(cards.begin() + i);
				--i;
			}
		}
		if (temp.size() > 1) repeats.push_back(temp);
	}
	return repeats;
}

std::vector<Card> WinnerDeterminant::getSequence(std::vector<Card> cards)
{
	std::vector<Card> sequence;
	sortCards(cards);
	std::vector<Card> tempAceStorage;

	if (cards.at(0).getBlanck().value == "A") tempAceStorage.push_back(cards.at(0));
	
	short count = 1;
	for (size_t i{ 0 }; i < cards.size() - 1; ++i)
	{
		short shortValue1 = convertValueToShort(cards.at(i).getBlanck().value);
		short shortValue2 = convertValueToShort(cards.at(i + 1).getBlanck().value);
		if (shortValue1 != shortValue2 + 1 && count != 5)
		{
			if (count < 4 && shortValue1 != shortValue2)
			{
				if (!i) cards.erase(cards.begin());
				else cards.erase(cards.begin(), cards.begin() + i);
				i = 0;
				count = 1;
			}
			else
			{
				cards.erase(cards.begin() + i + 1);
				--i;
			}
			continue;
		}
		else ++count;
	}
	if (cards.size() == 4 && isWheel(cards, tempAceStorage))
	{
		cards.push_back(tempAceStorage.at(0));
	}

	if (cards.size() < 5) return sequence;
	
	for (size_t i{ 0 }; i < 5; ++i)
	{
		sequence.push_back(cards.at(i));
	}
	return sequence;
}

inline short WinnerDeterminant::convertValueToShort(std::string value)
{
	if (value == "2") return 2;
	if (value == "3") return 3;
	if (value == "4") return 4;
	if (value == "5") return 5;
	if (value == "6") return 6;
	if (value == "7") return 7;
	if (value == "8") return 8;
	if (value == "9") return 9;
	if (value == "10") return 10;
	if (value == "J") return 11;
	if (value == "Q") return 12;
	if (value == "K") return 13;
	if (value == "A") return 14;
}

void WinnerDeterminant::sortCards(std::vector<Card>& cards)
{
	short size = cards.size();
	while (size--)
	{
		bool swapped = false;

		for (size_t i {0}; i < size; i++)
		{
			short shortValue1 = convertValueToShort(cards.at(i).getBlanck().value);
			short shortValue2 = convertValueToShort(cards.at(i + 1).getBlanck().value);
			if (shortValue1 < shortValue2)
			{
				std::swap(cards.at(i), cards.at(i + 1));
				swapped = true;
			}
		}

		if (swapped == false)
			return;
	}
}

bool WinnerDeterminant::isFlush(std::vector<Card>& cards)
{
	
	for (size_t i{ 0 }; i < cards.size(); ++i)
	{
		std::string suit = cards.at(i).getBlanck().suit;
		short count = 1;
		for (size_t j{ 0 }; j < cards.size(); ++j)
		{
			if (i == j) continue;
			std::string compare = cards.at(j).getBlanck().suit;
			if (suit == compare) ++count;
		}
		if (count >= 5) return true;
		count = 0;
	}
	return false;
}

bool WinnerDeterminant::isWheel(std::vector<Card> sequence, std::vector<Card> aceStorage)
{
	if (aceStorage.empty()) return false;
	std::string value1 = sequence.at(0).getBlanck().value;
	std::string value2 = sequence.at(1).getBlanck().value;
	std::string value3 = sequence.at(2).getBlanck().value;
	std::string value4 = sequence.at(3).getBlanck().value;

	if (value1 == "5" && value2 == "4" && value3 == "3" && value4 == "2") return true;
	return false;
}

void WinnerDeterminant::fillCombinationCards(short combinationID, short cardHolderID, std::vector<std::vector<Card>> repeats, std::vector<Card> sequence)
{
	switch (combinationID)
	{
	case 0:
		fillCombinationIfHighCard(cardHolderID);
		break;
	case 1:
		fillCombinationIfPair(cardHolderID, repeats);
		break;
	case 2:
		fillCombinationIfTwoPairs(cardHolderID, repeats);
		break;
	case 3:
		fillCombinationIfSet(cardHolderID, repeats);
		break;
	case 5:
		fillCombinationIfFlush(cardHolderID);
		break;
	case 6:
		fillCombinationIfFullHouse(cardHolderID, repeats);
		break;
	default:
		fillCombinationIfSequence(cardHolderID, sequence);
		break;
	}
}

void WinnerDeterminant::fillCombinationIfHighCard(short ID)
{
	switch (ID)
	{
	case 1:
		sortCards(sharedPlayerCards);
		for (size_t i{ 0 }; i < 5; ++i)
		{
			playerCombination.push_back(sharedPlayerCards.at(i));
		}
		break;
	case 2:
		sortCards(sharedCroupierCards);
		for (size_t i{ 0 }; i < 5; ++i)
		{
			croupierCombination.push_back(sharedCroupierCards.at(i));
		}
		break;
	}
	
}

void WinnerDeterminant::fillCombinationIfPair(short ID, std::vector < std::vector<Card>>  repeats)
{
	Card compare = repeats.at(0).at(0);

	switch (ID)
	{
	case 1:
		
		for (size_t i{ 0 }; i < sharedPlayerCards.size(); ++i)
		{
			if (sharedPlayerCards.at(i) == compare)
			{
				sharedPlayerCards.erase(sharedPlayerCards.begin() + i);
				--i;
			}
		}
		sortCards(sharedPlayerCards);
	
		for (size_t i{ 0 }; i < 2; ++i)
		{
			playerCombination.push_back(repeats.at(0).at(i));
		}
		for (size_t i{ 0 }; i < 3; ++i)
		{
			playerCombination.push_back(sharedPlayerCards.at(i));
		}	
		break;
	case 2:
		for (size_t i{ 0 }; i < sharedCroupierCards.size(); ++i)
		{
			if (sharedCroupierCards.at(i) == compare)
			{
				sharedCroupierCards.erase(sharedCroupierCards.begin() + i);
				--i;
			}
		}
		sortCards(sharedCroupierCards);

		for (size_t i{ 0 }; i < 2; ++i)
		{
			croupierCombination.push_back(repeats.at(0).at(i));
		}
		for (size_t i{ 0 }; i < 3; ++i)
		{
			croupierCombination.push_back(sharedCroupierCards.at(i));
		}
		break;
	}
}

void WinnerDeterminant::fillCombinationIfTwoPairs(short ID, std::vector<std::vector<Card>> repeats)
{
	if (repeats.size() == 3)
	{
		short minPairPointer = 0;
		for (size_t i{ 1 }; i < repeats.size(); ++i)
		{
			if (repeats.at(i).at(0) < repeats.at(i - 1).at(0)) minPairPointer = i;
		}

		repeats.erase(repeats.begin() + minPairPointer);
	}

	if (repeats.at(0).at(0) < repeats.at(1).at(0))
	{
		std::vector<Card> temp = repeats.at(0);
		repeats.at(0).clear();
		for (size_t i{ 0 }; i < 2; ++i)
		{
			repeats.at(0).push_back(repeats.at(1).at(i));
			repeats.at(1).at(i) = temp.at(i);
		}
	}

	Card firstCompare = repeats.at(0).at(0);
	Card secondCompare = repeats.at(1).at(0);
	switch (ID)
	{
	case 1:

		for (size_t i{ 0 }; i < sharedPlayerCards.size(); ++i)
		{
			if (sharedPlayerCards.at(i) == firstCompare || sharedPlayerCards.at(i) == secondCompare)
			{
				sharedPlayerCards.erase(sharedPlayerCards.begin() + i);
				--i;
			}
		}
		sortCards(sharedPlayerCards);

		for (size_t i{ 0 }; i < 2; ++i)
		{
			playerCombination.push_back(repeats.at(0).at(i));
		}
		for (size_t i{ 0 }; i < 2; ++i)
		{
			playerCombination.push_back(repeats.at(1).at(i));
		}

		playerCombination.push_back(sharedPlayerCards.at(0));	
		break;
	case 2:
		for (size_t i{ 0 }; i < sharedCroupierCards.size(); ++i)
		{
			if (sharedCroupierCards.at(i) == firstCompare || sharedCroupierCards.at(i) == secondCompare)
			{
				sharedCroupierCards.erase(sharedCroupierCards.begin() + i);
				--i;
			}
		}
		sortCards(sharedCroupierCards);

		for (size_t i{ 0 }; i < 2; ++i)
		{
			croupierCombination.push_back(repeats.at(0).at(i));
		}
		for (size_t i{ 0 }; i < 2; ++i)
		{
			croupierCombination.push_back(repeats.at(1).at(i));
		}

		croupierCombination.push_back(sharedCroupierCards.at(0));
		break;
	}
}

void WinnerDeterminant::fillCombinationIfSet(short ID, std::vector<std::vector<Card>> repeats)
{
	Card compare = repeats.at(0).at(0);

	switch (ID)
	{
	case 1:

		for (size_t i{ 0 }; i < sharedPlayerCards.size(); ++i)
		{
			if (sharedPlayerCards.at(i) == compare)
			{
				sharedPlayerCards.erase(sharedPlayerCards.begin() + i);
				--i;
			}
		}
		sortCards(sharedPlayerCards);

		for (size_t i{ 0 }; i < 3; ++i)
		{
			playerCombination.push_back(repeats.at(0).at(i));
		}
		for (size_t i{ 0 }; i < 2; ++i)
		{
			playerCombination.push_back(sharedPlayerCards.at(i));
		}
		break;
	case 2:
		for (size_t i{ 0 }; i < sharedCroupierCards.size(); ++i)
		{
			if (sharedCroupierCards.at(i) == compare)
			{
				sharedCroupierCards.erase(sharedCroupierCards.begin() + i);
				--i;
			}
		}
		sortCards(sharedCroupierCards);

		for (size_t i{ 0 }; i < 3; ++i)
		{
			croupierCombination.push_back(repeats.at(0).at(i));
		}
		for (size_t i{ 0 }; i < 2; ++i)
		{
			croupierCombination.push_back(sharedCroupierCards.at(i));
		}
		break;
	}
}

void WinnerDeterminant::fillCombinationIfFullHouse(short ID, std::vector<std::vector<Card>> repeats)
{
	std::vector<Card> set;
	std::vector<Card> pair;

	for (size_t i{ 0 }; i < repeats.size(); ++i)
	{
		if (repeats.at(i).size() == 3)
		{
			for (size_t j{ 0 }; j < 3; ++j) set.push_back(repeats.at(i).at(j));
			repeats.erase(repeats.begin() + i);
			break;
		}
	}

	if (repeats.size() == 2)
	{
		short minPairPointer = 0;
		for (size_t i{ 1 }; i < 2; ++i)
		{
			if (repeats.at(i).at(0) < repeats.at(i - 1).at(0)) minPairPointer = i;
		}
		repeats.erase(repeats.begin() + minPairPointer);
	}

	pair = repeats.at(0);
	
	switch (ID)
	{
	case 1:
		for (Card card : set) playerCombination.push_back(card);
		for (Card card : pair) playerCombination.push_back(card);
		break;

	case 2:
		pair = repeats.at(0);

		for (Card card : set) croupierCombination.push_back(card);
		for (Card card : pair) croupierCombination.push_back(card);
		break;
	}
}

void WinnerDeterminant::fillCombinationIfFlush(short ID)
{
	std::vector<Card> temp;

	switch (ID)
	{
	case 1:
		for (size_t i{ 0 }; i < sharedPlayerCards.size() - 2; ++i)
		{
			std::string suit = sharedPlayerCards.at(i).getBlanck().suit;
			temp.push_back(sharedPlayerCards.at(i));
			for (size_t j{ 0 }; j < sharedPlayerCards.size(); ++j)
			{
				if (i == j) continue;
				std::string compare = sharedPlayerCards.at(j).getBlanck().suit;
				if (suit == compare) temp.push_back(sharedPlayerCards.at(j));
			}
			if (temp.size() == 5) break;
			temp.clear();
		}
		sortCards(temp);
		for (Card card : temp) playerCombination.push_back(card);
		break;
	case 2:
		for (size_t i{ 0 }; i < sharedCroupierCards.size() - 2; ++i)
		{
			std::string suit = sharedCroupierCards.at(i).getBlanck().suit;
			temp.push_back(sharedCroupierCards.at(i));
			for (size_t j{ 0 }; j < sharedCroupierCards.size(); ++j)
			{
				if (i == j) continue;
				std::string compare = sharedCroupierCards.at(j).getBlanck().suit;
				if (suit == compare) temp.push_back(sharedCroupierCards.at(j));
			}
			if (temp.size() == 5) break;
			temp.clear();		
		}
		sortCards(temp);
		for (Card card : temp) croupierCombination.push_back(card);
		break;
	}	
}

void WinnerDeterminant::fillCombinationIfSequence(short ID, std::vector<Card> sequence)
{
	switch (ID)
	{
	case 1:
		for (Card card : sequence) playerCombination.push_back(card);
		break;
	case 2: 
		for (Card card : sequence) croupierCombination.push_back(card);
		break;
	}
	
}

