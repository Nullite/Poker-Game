#include "Card.h"

inline short Card::convertValueToShort(std::string value)
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

Card::Card()
{
	cardBack = "+++++++++\n++     ++\n+ +   + +\n+   +   +\n+ +   + +\n++     ++\n+++++++++";
	card = "+++++++++\n+       +\n+       +\n+       +\n+       +\n+       +\n+++++++++";
	valuePointer = counter == 3 ? ++valuePointer : valuePointer;
	counter = counter == 3 ? 0 : ++counter;
	blanck.suit = suit;
	blanck.value = value.at(valuePointer);
	if (blanck.value == "10")
	{
		card.replace(12, 2, blanck.value);
		card.replace(55, 2, blanck.value);
	}
	else
	{
		card.replace(12, 1, blanck.value);
		card.replace(56, 1, blanck.value);
	}
	if (suit == hearts || suit == diamond)
	{
		std::string temp = "\x1b[31m" + blanck.suit + "\x1b[0m";
		card.replace(34, 1, temp);
	}
	else
	{
		card.replace(34, 1, blanck.suit);
	}
	
	suit = suit == peak ? hearts : ++suit;
}

std::string Card::getCard()
{
	return card;
}

Blanck Card::getBlanck()
{
	return blanck;
}

std::string Card::getCardBack()
{
	return cardBack;
}

bool operator==(Card& card1, Card& card2)
{
	return card1.blanck.value == card2.blanck.value && card1.blanck.suit == card2.blanck.suit;
}

bool operator>(Card& card1, Card& card2)
{
	return Card::convertValueToShort(card1.blanck.value) > Card::convertValueToShort(card2.blanck.value);
}

bool operator<(Card& card1, Card& card2)
{
	return Card::convertValueToShort(card1.blanck.value) < Card::convertValueToShort(card2.blanck.value);
}
