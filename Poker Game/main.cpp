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
		while (1)
		{
			game.initRound(deck, player, croupier);
			game.round(deck, player, croupier, table);
			game.showDown(croupier, player, table);
			game.askContinue();
			game.waitContinue();
			game.endRound(deck, player, croupier, table);
			if (game.checkIsPartyOver(player, croupier))
			{
				if (!player.getChips())
				{
					if (game.isContinue(player)) continue;
				}
				exit(0);
			}
		}
	}
	catch (const char* exept)
	{
		system("cls");
		std::cout << exept;
		exit(1);
	}
}