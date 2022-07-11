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

std::string Interface::getLineTodisplay(size_t& from, std::string _where)
{
	std::string displayLine;
	for (from; ; from++)
	{
		if (from == _where.size()) return displayLine;
		if (_where.at(from) == '\n') return displayLine;
		displayLine += _where.at(from);
	}
}

bool Interface::checkIfRedSuit(std::string card)
{
	for (size_t i{ 0 }; i < card.size(); i++)
	{
		if (card.at(i) == '\x1b') return true;
	}
	return false;
}

Interface::Interface()
{
	chipsPlaceHolder = "+++++++++++++++\n+             +\n+++++++++++++++";
	actionPlaceHolder = "+++++++++++++++++++++++++++++++++\n+       +        +       +      + \n+  \x1b[36mBET\x1b[0m  + \x1b[33m3x BET\x1b[0m + \x1b[32mCHECK\x1b[0m + \x1b[31mFOLD\x1b[0m +\n+       +        +       +      +\n+++++++++++++++++++++++++++++++++";
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
		for (size_t j{ 0 }; j < blanck.size(); j++)
		{
			std::string displayLine = getLineTodisplay(j, blanck);
			std::cout << displayLine;
				cursor = getCursor();
				if (checkIfRedSuit(displayLine)) cursor.X -= displayLine.size() - 9;
				else cursor.X -= displayLine.size();
				cursor.Y++;
				setCursor(cursor);
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
	std::cout << "      ";
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
	cursor.X = 0;
	cursor.Y = 0;
	setCursor(cursor);
	for (size_t i{ 0 }; i < chipsPlaceHolder.size(); i++)
	{
		std::string displayLine = getLineTodisplay(i, chipsPlaceHolder);
		cursor = getCursor();
		cursor.X = 0;
		cursor.Y++;
		setCursor(cursor);
		std::cout << displayLine;
	}

	cursor.X = 2;
	cursor.Y = 19;
	setCursor(cursor);
	std::cout << "Your chips:\n";
	cursor.X = 0;
	cursor.Y = 19;
	setCursor(cursor);
	for (size_t i{ 0 }; i < chipsPlaceHolder.size(); i++)
	{
		std::string displayLine = getLineTodisplay(i, chipsPlaceHolder);
		cursor = getCursor();
		cursor.X = 0;
		cursor.Y++;
		setCursor(cursor);
		std::cout << displayLine;
	}	
}

void Interface::showActionPlaceHolder()
{
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 24;
	setCursor(cursor);
	for (size_t i{ 0 }; i < actionPlaceHolder.size(); i++)
	{
		std::string displayLine = getLineTodisplay(i, actionPlaceHolder);
			cursor = getCursor();
			cursor.X = 0;
			cursor.Y++;
			setCursor(cursor);
		std::cout << displayLine;
	}
}

