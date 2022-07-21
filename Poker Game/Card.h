#pragma once
#include <vector>
#include <string>
#include <iostream>

struct Blanck
{
	std::string suit;
	std::string value;
};
class Card
{
	Blanck blanck;
	enum {hearts = 3, diamond, club, peak};
	std::vector<const char*> value{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	static inline short counter = -1;
	static inline char suit = hearts;
	static inline short valuePointer = 0;
	
	std::string card;
	std::string cardBack;
public:
	
	Card();
	std::string getCard();
	Blanck getBlanck();
	std::string getCardBack();
	friend bool operator == (Card& card1, Card& card2);
	friend bool operator > (Card& card1, Card& card2);
	friend bool operator < (Card& card1, Card& card2);
	const friend std::ostream& operator << (std::ostream& out, Card& card);
	static inline short convertValueToShort(std::string value);
 };