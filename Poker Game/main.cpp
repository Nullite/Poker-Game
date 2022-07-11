#include "interface.h"

int main()
{
	try
	{
		Interface game;
		Deck deck;
		deck.shuffle();
		Player player;
		Croupier croupier;
		Table table;
		player.takeCards(deck);
		croupier.takeCards(deck);
		table.takeCards(deck);
		game.showCards(player, true);
		game.showCards(croupier, false);
		game.showCards(table, true);
		Sleep(5000);
		table.takeCards(deck);
		game.showCards(table, true);
		Sleep(5000);
		table.takeCards(deck);
		game.showCards(table, true);
		Sleep(5000);
		game.showCards(croupier, true);
		Sleep(5000);
		game.endRound(deck, player, croupier, table);
		player.takeCards(deck);
		croupier.takeCards(deck);
		table.takeCards(deck);
		game.showCards(player, true);
		game.showCards(croupier, false);
		game.showCards(table, true);
		Sleep(5000);
		table.takeCards(deck);
		game.showCards(table, true);
		Sleep(5000);
		table.takeCards(deck);
		game.showCards(table, true);
		Sleep(5000);
		game.showCards(croupier, true);
		Sleep(5000);
		Sleep(1000000000000);
	}
	catch (const char* exept)
	{
		system("cls");
		std::cout << exept;
		exit(0);
	}
	
}

