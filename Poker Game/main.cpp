#include "interface.h"

int main()
{
	Interface game;
	Player player;
	Croupier croupier;
	try
	{
		game.showChipsPlaceHolders();
		game.showChips(player);
		game.showChips(croupier);
		Sleep(100000000);
	}
	catch (const char* exept)
	{
		system("cls");
		std::cout << exept;
		exit(0);
	}
	
}

