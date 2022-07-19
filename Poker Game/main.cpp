#include "Interface.h"

int main()
{
	Interface game;
	Deck deck;
	Player player;
	Croupier croupier;
	Table table;
	
	try
	{
		/*deck.shuffle();*/
		/*deck.check();
		player.takeCards(deck);
		croupier.takeCards(deck);
		table.takeCards(deck);
		table.takeCards(deck);
		table.takeCards(deck);
		WinnerDeterminant whoseWin(player, croupier, table);
		whoseWin.combinationHandler(player);
		whoseWin.combinationHandler(croupier);
		std::vector<Card> croupierCards = croupier.getCards();
		std::vector<Card> tableCards = table.getCards();
		std::vector<Card> playerCards = player.getCards();
		short whoWin = whoseWin.compareCombinations();
		std::vector<Card> combination = whoseWin.getPlayerCombination();
		std::vector<Card> croupierCombination = whoseWin.getCroupierCombination();
		for (Card card : croupierCards) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		for (Card card : tableCards) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		for (Card card : playerCards) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		for (Card card : combination) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		for (Card card : croupierCombination) std::cout << card.getBlanck().value << card.getBlanck().suit << ' ';
		std::cout << '\n';
		std::cout << whoWin;*/
		while (1)
		{
			game.initRound(deck, player, croupier);
			game.round(deck, player, croupier, table);
			game.showDown(croupier, player, table);
			Sleep(10000);
			game.endRound(deck, player, croupier, table);
			if (game.checkIsPartyOver(player, croupier)) exit(0);
		}
	}
	catch (const char* exept)
	{
		system("cls");
		std::cout << exept;
		exit(1);
	}
}