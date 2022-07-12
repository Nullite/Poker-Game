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
		game.showBankPlaceHolder();
		game.showBank();
		game.showCards(player, true);
		game.showCards(croupier, false);
		game.showCards(table, true);
		game.selectMenuActions();
		player.bet(50);
		croupier.bet(50);
		game.showChips(croupier);
		table.takeCards(deck);
		game.selectMenuActions();
		game.showCards(table, true);
		table.takeCards(deck);
		game.selectMenuActions();
		game.showCards(table, true);
		game.selectMenuActions();
		game.showCards(croupier, true);
		game.selectMenuActions();
	}
	catch (const char* exept)
	{
		system("cls");
		std::cout << exept;
		exit(0);
	}
	
}

