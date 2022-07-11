#include "interface.h"

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
		game.showChipsPlaceHolders();
		game.showChips(player);
		game.showChips(croupier);
		game.showActionPlaceHolder();
		game.showCards(player, true);
		game.showCards(croupier, false);
		game.showCards(table, true);
		Sleep(100000000);
	}
	catch (const char* exept)
	{
		system("cls");
		std::cout << exept;
		exit(0);
	}
	
}

