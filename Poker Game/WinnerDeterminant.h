#pragma once
#include "CardHolder.h"
class WinnerDeterminant
{
	enum {highCard, pair, twoPairs, set, straight, flush, fullHouse, fourOfTheKind, straightFlush, royalFlush};
	std::vector<Card> playerCards;
	std::vector<Card> croupierCards;
	std::vector<Card> tableCards;
	std::vector<Card> sharedPlayerCards;
	std::vector<Card> sharedCroupierCards;
	std::vector<Card> playerCombination;
	std::vector<Card> croupierCombination;
	short playerCobinationID;
	short croupierCombinationID;

	static inline short convertValueToShort(std::string value);
	short getRepeatCombinationID(std::vector<std::vector<Card>>& repeats);
	short getSequenceCombinationID(std::vector<Card> sequence, bool isFlush);
	std::vector < std::vector<Card>> getRepeats(std::vector<Card> cards);
	std::vector<Card> getSequence(std::vector<Card> cards);
	
	void fillSharedCards(CardHolder& cardHolder);
	void sortCards(std::vector<Card>& cards);
	bool isFlush(std::vector<Card>& cards);
	bool isWheel(std::vector<Card> sequence, std::vector<Card> aceStorage);
	void fillCombinationCards(short combinationID, short cardHolderID, std::vector < std::vector<Card>> repeats, std::vector<Card> sequence);
	void fillCombinationIfHighCard(short ID);
	void fillCombinationIfPair(short ID, std::vector < std::vector<Card>> repeats);
	void fillCombinationIfTwoPairs(short ID, std::vector < std::vector<Card>> repeats);
	void fillCombinationIfSet(short ID, std::vector < std::vector<Card>> repeats);
	void fillCombinationIfFullHouse(short ID, std::vector < std::vector<Card>> repeats);
	void fillCombinationIfFlush(short ID);
	void fillCombinationIfSequence(short ID, std::vector<Card> sequence);
	
public:
	
	WinnerDeterminant(CardHolder& player, CardHolder& croupier, CardHolder& table);
	WinnerDeterminant(CardHolder& player, CardHolder& table);
	void combinationHandler(CardHolder& cardHolder);
	short compareCombinations();
	short getPlayerCombinationID();
	short getCroupierCombinationID();
	std::vector<Card> getPlayerCombination();
	std::vector<Card> getCroupierCombination();
};

