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
	/*	deck.shuffle();*/
		deck.getFullHouse();
		player.takeCards(deck);
	/*	croupier.takeCards(deck);*/
		table.takeCards(deck);
		table.takeCards(deck);
		table.takeCards(deck);
		WinnerDeterminant whoseWin(player, croupier, table);
		whoseWin.fillSharedCards(player);
		short a = whoseWin.combinationHandler(player);
		std::vector<Card> tableCards = table.getCards();
		std::vector<Card> playerCards = player.getCards();
		std::vector<Card> combination = whoseWin.getPlayerCombination();
		for (Card card : tableCards) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		for (Card card : playerCards) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		for (Card card : combination) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		std::cout << a;
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

