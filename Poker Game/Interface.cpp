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
	roundCount = 0;
	bank = 0;
	bankPlaceHolder = "+++++++++++++++\n+             +\n+++++++++++++++";
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
	bank = 0;
	roundCount = 0;
	deck.endRound();
	player.endRound();
	croupier.endRound();
	table.endRound();
	clearTable();
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

void Interface::eraseUnderLine(short action)
{
	if (action < 1 || action > 4) throw "action must be from 1 to 4";
	std::string frame = "       \n+++++++";
	COORD cursor;
	if (action == 4)
	{
		frame.erase(frame.begin());
		frame.erase(frame.end());
	}
	else if (action == 2)
	{
		frame.insert(frame.begin(), ' ');
		frame.insert(frame.end(), '+');
	}
	int target = action == 1 ? 1 : action == 2 ? 9 : action == 3 ? 18 : 26;
	cursor.X = target;
	cursor.Y = 27;
	setCursor(cursor);
	for (size_t i{ 0 }; i < frame.size(); i++)
	{
		std::string displayLine = getLineTodisplay(i, frame);
		cursor = getCursor();
		cursor.X = target;
		cursor.Y++;
		setCursor(cursor);
		std::cout << displayLine;
	}
}

void Interface::clearTable()
{
	COORD cursor;
	cursor.X = 35;
	cursor.Y = 10;
	setCursor(cursor);
	for (size_t i{ 0 }; i < 16; ++i)
	{
		std::cout << "                                                 ";
		cursor.Y++;
	}
}

short Interface::selectMenuActions()
{
	short cursor = 1;
	underlineMenuActions(cursor);
	while (1)
	{
		short action = _getch();
		if (action == -32) action = _getch();
		else if (action == 13) 
		{
			eraseUnderLine(cursor);
			return cursor;
		}
		switch (action)
		{
		case 77:
			if (cursor < 4)
			{
				eraseUnderLine(cursor);
				underlineMenuActions(++cursor);
			}
			
			break;
		case 75:
			if (cursor > 1)
			{
				eraseUnderLine(cursor);
				underlineMenuActions(--cursor);
			}	
		}
	}
}

void Interface::showBankPlaceHolder()
{
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 10;
	setCursor(cursor);
	std::cout << "bank:\n";
	cursor.X = 0;
	cursor.Y = 10;
	setCursor(cursor);
	for (size_t i{ 0 }; i < bankPlaceHolder.size(); i++)
	{
		std::string displayLine = getLineTodisplay(i, bankPlaceHolder);
		cursor = getCursor();
		cursor.X = 0;
		cursor.Y++;
		setCursor(cursor);
		std::cout << displayLine;
	}
}

void Interface::showBank()
{
	COORD cursor;
	cursor.X = 2;
	cursor.Y = 12;
	setCursor(cursor);
	std::cout << "          ";
	cursor.X = bank < 10 ? 7 : bank < 1000 ? 6 : 5;
	setCursor(cursor);
	std::cout << bank;
}

void Interface::bet(short bet, CardHolder& cardHolder)
{
	if (bet < 1 || bet > 3) throw "bet have only three optons: 1 - bet, 2 - 3x bet, 3 - blind";
	bet = bet == 1 ? 50 : bet == 2 ? 150 : 25;
	cardHolder.bet(bet);
	showChips(cardHolder);
	bank += bet;
	showBank();
}

bool Interface::action(CardHolder& player, CardHolder& croupier)
{
	short action = selectMenuActions();
	if (action != 4)
	{
		this->bet(action, player);
		this->bet(action, croupier);
		return true;
	}
		croupier.winChips(bank);
		showChips(croupier);
		bank = 0;
		showBank();
		return false;
}

void Interface::initRound(Deck& deck, CardHolder& player, CardHolder& croupier)
{
	showChipsPlaceHolders();
	showChips(player);
	showChips(croupier);
	showActionPlaceHolder();
	showBankPlaceHolder();
	showBank();

	deck.shuffle();
	player.takeCards(deck);
	croupier.takeCards(deck);
	showCards(player, true);
	showCards(croupier, false);
	Sleep(1000);
	bet(3, player);
	bet(3, croupier);
}

void Interface::round(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table)
{
	bool isAction = action(player, croupier);
	++roundCount;
	while (isAction && roundCount < 4)
	{
		table.takeCards(deck);
		showCards(table, true);
		isAction = action(player, croupier);
		++roundCount;
	}
}

void Interface::showDown(CardHolder& croupier)
{
	showCards(croupier, true);
}

void Interface::underlineMenuActions(short action)
{
	if (action < 1 || action > 4) throw "action must be from 1 to 4";
	std::string frame = "\x1b[31m+++++++\n+++++++\x1b[0m";
	COORD cursor;
	if (action == 4) 
	{
		frame.erase(frame.begin() + 5);
		frame.erase(frame.end() - 5);
	}
	else if (action == 2)
	{
		std::string::iterator it = frame.begin() + 5;
		for (;it < frame.begin() + 6; ++it)
		{
			frame.insert(it, '+');
		}
		for (it = frame.end() - 5; it > frame.end() - 7; --it)
		{
			frame.insert(it, '+');
		}
	}
	int target = action == 1 ? 1 : action == 2 ? 9 : action == 3 ? 18 : 26;
	cursor.X = target;
	cursor.Y = 27;
	setCursor(cursor);
	for (size_t i{ 0 }; i < frame.size(); i++)
	{
		std::string displayLine = getLineTodisplay(i, frame);
		cursor = getCursor();
		cursor.X = target;
		cursor.Y++;
		setCursor(cursor);
		std::cout << displayLine;
	}
}

