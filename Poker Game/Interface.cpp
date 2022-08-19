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
	clearWinDisplay();
	clearTable();
	clearCombination(player);
	clearCombination(croupier);
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

void Interface::displayCombination(short ID, short combinationID, std::vector<Card> combination)
{
	std::string stringCombination = convertCombinationIDToString(combinationID);
	COORD cursor;
	switch (ID)
	{
	case 1:
		cursor.X = 80;
		cursor.Y = 25;
		setCursor(cursor);
		std::cout << "                    ";
		cursor.Y++;
		setCursor(cursor);
		std::cout << "                    ";
		cursor.Y--;
		setCursor(cursor);
		std::cout << stringCombination << ':';
		cursor.Y++;
		setCursor(cursor);
		for (size_t i{ 0 }; i < combination.size(); ++i)
		{
			std::cout << combination.at(i);
			std::cout << ' ';
		}
		break;
	case 2:
		cursor.X = 80;
		cursor.Y = 2;
		setCursor(cursor);
		std::cout << "                    ";
		cursor.Y++;
		setCursor(cursor);
		std::cout << "                    ";
		cursor.Y--;
		setCursor(cursor);
		std::cout << stringCombination << ':';
		cursor.Y++;
		setCursor(cursor);
		for (size_t i{ 0 }; i < combination.size(); ++i)
		{
			std::cout << combination.at(i).getBlanck().value << combination.at(i).getBlanck().suit << ' ';
		}
		break;
	}
}

std::string Interface::convertCombinationIDToString(short combinationID)
{
	switch (combinationID)
	{
	case 0:
		return "High Card";
	case 1:
		return "Pair";
	case 2:
		return "Two Pairs";
	case 3:
		return "Set";
	case 4:
		return "Straight";
	case 5:
		return "Flush";
	case 6:
		return "Fullhouse";
	case 7:
		return "Four Of The Kind";
	case 8:
		return "Straight-Flush";
	case 9:
		return "Royal-Flush";
	}
}

void Interface::clearCombination(CardHolder& cardHolder)
{
	short ID = cardHolder.getID();
	COORD cursor;
	switch (ID)
	{
	case 1:
		cursor.X = 80;
		cursor.Y = 25;
		setCursor(cursor);
		std::cout << "                ";
		cursor.Y++;
		setCursor(cursor);
		std::cout << "                ";
		break;
	case 2:
		cursor.X = 80;
		cursor.Y = 2;
		setCursor(cursor);
		std::cout << "                ";
		cursor.Y++;
		setCursor(cursor);
		std::cout << "                ";
		break;
	}
}

void Interface::displayWin(short ID)
{
	COORD cursor;
	cursor.X = 85;
	cursor.Y = 12;
	setCursor(cursor);
	switch (ID)
	{
	case 0:
		std::cout << "YOU SPLIT THE BANK $" << bank/2;
		cursor.Y++;
		setCursor(cursor);
		std::cout << "CROUPIER SPLIT THE BANK $" << bank / 2;
		break;
	case 1:
		std::cout << "YOU WIN $" << bank;
		break;
	case 2:
		std::cout << "CROUPIER WIN $" << bank;
		break;
	}
}

void Interface::clearWinDisplay()
{
	COORD cursor;
	cursor.X = 80;
	cursor.Y = 12;
	setCursor(cursor);
	std::cout << "               ";
	cursor.Y++;
	setCursor(cursor);
	std::cout << "               ";
}

bool Interface::isAllIn(CardHolder& player, CardHolder& croupier)
{
	if (player.getChips() == 0 || croupier.getChips() == 0) return true;
	return false;
}

void Interface::showAllin(CardHolder& player, CardHolder& croupier)
{
	COORD cursor;
	if (!player.getChips())
	{
		cursor.X = 5;
		cursor.Y = 21;
		setCursor(cursor);
		std::cout << "\x1b[31mALL IN\x1b[0m";
	}
	if (!croupier.getChips())
	{
		cursor.X = 5;
		cursor.Y = 2;
		setCursor(cursor);
		std::cout << "\x1b[31mALL IN\x1b[0m";
	}
	
	
}

void Interface::showChipsChange(CardHolder& cardHolder, bool isBet, short change)
{
	short ID = cardHolder.getID();
	COORD cursor;
	if (ID == 1)
	{
		cursor.X = 5;
		cursor.Y = 21;
		setCursor(cursor);
		std::cout << "        ";
		setCursor(cursor);
		if (isBet) std::cout << "\x1b[31m-" << change << "\x1b[0m";
		else std::cout << "\x1b[32m+" << change << "\x1b[0m";
	}
	if (ID == 2)
	{
		cursor.X = 5;
		cursor.Y = 2;
		setCursor(cursor);
		std::cout << "        ";
		setCursor(cursor);
		if (isBet) std::cout << "\x1b[31m-" << change << "\x1b[0m";
		else std::cout << "\x1b[32m+" << change << "\x1b[0m";
	}
}

void Interface::askIfRebuy(CardHolder& cardHolder)
{
	short ID = cardHolder.getID();
	std::string askPlaceHolder = "+++++++++++++++++++++++++\n+                       +\n+++++++++++++++++++++++++\n+           +           +\n+++++++++++++++++++++++++";
	COORD cursor;
	cursor.X = 45;
	cursor.Y = 12;
	setCursor(cursor);
	for (size_t i{ 0 }; i < askPlaceHolder.size(); i++)
	{
		std::string displayLine = getLineTodisplay(i, askPlaceHolder);
		cursor.Y++;
		setCursor(cursor);
		std::cout << displayLine;
	}
	cursor.X = 47;
	cursor.Y = 14;
	setCursor(cursor);
	ID == 1 ? std::cout << "\x1b[32mDO YOU WANT TO REBUY?\x1b[0m" : std::cout << "\x1b[32mDO YOU WANNA CONTINUE?\x1b[0m";
	cursor.X = 50;
	cursor.Y = 16;
	setCursor(cursor);
	std::cout << "\x1b[33mYES\x1b[0m";
	cursor.X = 63;
	setCursor(cursor);
	std::cout << "\x1b[31mNO\x1b[0m";
}

void Interface::underlineRebuyMenu(short menu)
{
	std::string frame = "\x1b[31m+++++++++++\x1b[0m";
	COORD cursor;
	short target = menu == 1 ? 46 : 58;
	cursor.X = target;
	cursor.Y = 17;
	setCursor(cursor);
	std::cout << frame;
}

void Interface::eraseUnderlineRebuyMenu(short menu)
{
	std::string frame = "+++++++++++";
	COORD cursor;
	short target = menu == 1 ? 46 : 58;
	cursor.X = target;
	cursor.Y = 17;
	setCursor(cursor);
	std::cout << frame;
}

bool Interface::checkIfWantToContinue(CardHolder& cardholder)
{
	askIfRebuy(cardholder);
	short cursor = 1;
	underlineRebuyMenu(1);
	while (1)
	{
		short action = _getch();
		if (action == -32) action = _getch();
		else if (action == 13)
		{
			eraseUnderlineRebuyMenu(cursor);
			return cursor == 1 ? true : false;
		}
		switch (action)
		{
		case 77:
			if (cursor < 2)
			{
				eraseUnderlineRebuyMenu(cursor);
				underlineRebuyMenu(++cursor);
			}

			break;
		case 75:
			if (cursor > 1)
			{
				eraseUnderlineRebuyMenu(cursor);
				underlineRebuyMenu(--cursor);
			}
		}
	}
}

void Interface::eraseRebuyMenu()
{
	std::string erase = "                           ";
	COORD cursor;
	cursor.X = 45;
	cursor.Y = 12;
	setCursor(cursor);
	for (size_t i{ 0 }; i < 7; i++)
	{
		std::cout << erase;
		cursor.Y++;
		setCursor(cursor);
	}
}

bool Interface::isContinue(CardHolder& cardHolder)
{
	if (checkIfWantToContinue(cardHolder))
	{
		cardHolder.setChips();
		eraseRebuyMenu();
		return true;
	}
	eraseRebuyMenu();
	return false;
}

void Interface::askContinue()
{
	COORD cursor;
	cursor.X = 1;
	cursor.Y = 26;
	setCursor(cursor);
	std::cout << "                              ";
	cursor.Y++;
	setCursor(cursor);
	std::cout << "           \x1b[33mCONTINUE\x1b[0m           ";
	cursor.Y++;
	setCursor(cursor);
	std::cout << "\x1b[31m+++++++++++++++++++++++++++++++\x1b[0m";
	cursor.Y++;
	setCursor(cursor);
	std::cout << "\x1b[31m+++++++++++++++++++++++++++++++\x1b[0m";
}

void Interface::waitContinue()
{
	while (true)
	{
		char isContinue = _getch();
		if (isContinue == 13) return;
	}
}

bool Interface::checkIsPartyOver(CardHolder& player, CardHolder& croupier)
{
	if (player.getChips() == 0 || croupier.getChips() == 0) return true;
	return false;
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
	cardHolder.bet(bet);
	showChipsChange(cardHolder, true, bet);
	Sleep(500);
	showChips(cardHolder);
	bank += bet;
	showBank();
}

bool Interface::action(CardHolder& player, CardHolder& croupier)
{
	short action = selectMenuActions();
	if (action != 4)
	{
		short bet = action == 1 ? 50 : action == 2 ? 150 : 25;
		short playerChips = player.getChips();
		short croupierChips = croupier.getChips();
		if (bet > playerChips) bet = playerChips;
		else if (bet > croupierChips) bet = croupierChips;
		this->bet(bet, player);
		this->bet(bet, croupier);
		return true;
	}
		return false;
}

void Interface::initRound(Deck& deck, CardHolder& player, CardHolder& croupier)
{
	isFold = false;
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
	bet(25, player);
	bet(25, croupier);
}

void Interface::round(Deck& deck, CardHolder& player, CardHolder& croupier, CardHolder& table)
{
	bool isAction = action(player, croupier);
	if (!isAction) isFold = true;
	++roundCount;
	while (isAction && roundCount < 4)
	{
		table.takeCards(deck);
		showCards(table, true);
		WinnerDeterminant checkCombination(player, table);
		checkCombination.combinationHandler(player);
		std::vector<Card> playerCombination = checkCombination.getPlayerCombination();
		short combinationID = checkCombination.getPlayerCombinationID();
		displayCombination(player.getID(), combinationID, playerCombination);
		if (!isAllIn(player, croupier)) isAction = action(player, croupier);
		else
		{
			showAllin(player, croupier);
			Sleep(1000);
		}
		++roundCount;
		if (!isAction) isFold = true;
	}
}

void Interface::showDown(CardHolder& croupier, CardHolder& player, CardHolder& table)
{
	showCards(croupier, true);
	if (!isFold)
	{
		WinnerDeterminant whoseWin(player, croupier, table);
		whoseWin.combinationHandler(player);
		whoseWin.combinationHandler(croupier);
		std::vector<Card> croupierCombination = whoseWin.getCroupierCombination();
		short croupierCombinationID = whoseWin.getCroupierCombinationID();
		displayCombination(croupier.getID(), croupierCombinationID, croupierCombination);
		short whoWin = whoseWin.compareCombinations();
		if (whoWin == 1)
		{
			player.winChips(bank);
			displayWin(player.getID());
			showChipsChange(player, false, bank);
			bank = 0;
			Sleep(1000);
		}
		else if (whoWin == 2)
		{
			croupier.winChips(bank);
			displayWin(croupier.getID());
			showChipsChange(croupier, false, bank);
			bank = 0;
			Sleep(1000);
		}
		else
		{
			player.winChips(bank / 2);
			croupier.winChips(bank / 2);
			displayWin(0);
			showChipsChange(player, false, bank / 2);
			showChipsChange(croupier, false, bank / 2);
			bank = 0;
			Sleep(1000);
		}
	}
	else
	{
		croupier.winChips(bank);
		displayWin(croupier.getID());
		showChipsChange(croupier, false, bank);
		bank = 0;
		Sleep(1000);
		if (roundCount > 1)
		{
			WinnerDeterminant whoseWin(player, croupier, table);
			whoseWin.combinationHandler(player);
			whoseWin.combinationHandler(croupier);
			std::vector<Card> croupierCombination = whoseWin.getCroupierCombination();
			short croupierCombinationID = whoseWin.getCroupierCombinationID();
			displayCombination(croupier.getID(), croupierCombinationID, croupierCombination);
		}
	}
	showBank();
	showChips(player);
	showChips(croupier);
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

