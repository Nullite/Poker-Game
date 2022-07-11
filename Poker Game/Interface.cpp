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

void Interface::showCards(CardHolder& player, bool isFace)
{
	int whoseCards = player.getID();
	std::vector<Card> deck;
	deck = player.getCards();
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

