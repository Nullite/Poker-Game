#include "interface.h"
#include "WinnerDeterminant.h"

int main()
{
	Interface game;
	Deck deck;
	Player player;
	Croupier croupier;
	Table table;
	
	try
	{
		deck.shuffle();
		player.takeCards(deck);
		croupier.takeCards(deck);
		table.takeCards(deck);
		table.takeCards(deck);
		table.takeCards(deck);
		WinnerDeterminant whoseWin(player, croupier, table);
	//	/*while (1)
	//	{
	//		game.initRound(deck, player, croupier);
	//		game.round(deck, player, croupier, table);
	//		game.showDown(croupier);
	//		Sleep(10000);
	//		game.endRound(deck, player, croupier, table);
	//	}
	}
	catch (const char* exept)
	{
		system("cls");
		std::cout << exept;
		exit(0);
	}
	
}

