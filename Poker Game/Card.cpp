#include "Card.h"

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
	card.replace(34, 1, blanck.suit);
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

