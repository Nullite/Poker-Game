#include "Interface.h"

COORD Interface::getCursor()
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buf;
	if (GetConsoleScreenBufferInfo(hCon, &buf))
	{
		return buf.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void Interface::setCursor(COORD coord)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, coord);
}

Interface::Interface()
{
	chipsPlaceHolder = "+++++++++++++++\n+             +\n+++++++++++++++";
}

void Interface::showCards(CardHolder& cardHolder, bool isFace)
{
	int whoseCards = cardHolder.getID();
	std::vector<Card> deck;
	deck = cardHolder.getCards();
	short quantity = deck.size();
	COORD cursor;
	cursor.X = quantity == 2 ? 50 : quantity == 3 ? 45 : quantity == 4 ? 40 : 35;
	if (whoseCards == 3) cursor.X += 2;
	short high = whoseCards == 1 ? 20 : whoseCards == 2 ? 0 : 10;
	cursor.Y = high;
	setCursor(cursor);
	for (size_t i{ 0 }; i < quantity; i++)
	{
		Card card = deck.at(i);
		std::string blanck = isFace ? card.getCard() : card.getCardBack();
		int count = 0;
		for (size_t j{ 0 }; j < blanck.size(); j++)
		{
			if (blanck.at(j) == '\n')
			{
				cursor = getCursor();
				cursor.X -= count;
				cursor.Y++;
				setCursor(cursor);
				count = 0;
				continue;
			}
			std::cout << blanck.at(j);
			count++;
		}
		cursor.X += whoseCards == 3 ? 9 : 10;	
		cursor.Y = high;
		setCursor(cursor);
	}
}

void Interface::endRound(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table)
{
	deck.endRound();
	player.endRound();
	croupier.endRound();
	table.endRound();
	system("cls");
}

void Interface::showChips(CardHolder& cardholder)
{
	short whoseChips = cardholder.getID();
	if (whoseChips < 1 || whoseChips > 2) throw "only player and croupier have chips to show";
	short chips = cardholder.getChips();
	COORD cursor;
	cursor.X = 5;
	cursor.Y = whoseChips == 1 ? 21 : 2;
	setCursor(cursor);
	std::cout << '$' << chips;
}

void Interface::showChipsPlaceHolders()
{
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 0;
	setCursor(cursor);
	std::cout << "Croupier chips:\n";
	short count = 0;
	for (size_t i{ 0 }; i < chipsPlaceHolder.size(); i++)
	{
		if (chipsPlaceHolder.at(i) == '\n')
		{
			cursor = getCursor();
			cursor.X -= count;
			cursor.Y++;
			setCursor(cursor);
			count = 0;
			continue;
		}
		std::cout << chipsPlaceHolder.at(i);
		count++;
	}

	cursor.X = 2;
	cursor.Y = 19;
	setCursor(cursor);
	std::cout << "Your chips:\n";
	cursor.X = 0;
	cursor.Y++;
	setCursor(cursor);
	count = 0;
	for (size_t i{ 0 }; i < chipsPlaceHolder.size(); i++)
	{
		if (chipsPlaceHolder.at(i) == '\n')
		{
			cursor = getCursor();
			cursor.X -= count;
			cursor.Y++;
			setCursor(cursor);
			count = 0;
			continue;
		}
		std::cout << chipsPlaceHolder.at(i);
		count++;
	}
	
}

