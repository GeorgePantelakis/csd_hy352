#ifndef ROUND_H
#define ROUND_H
#include <iostream>
#include "Magic.h"

class Round {
private:
	int roundNum = 1;
	Magic::Wizard* turn;
	std::map<int, std::vector<std::pair<std::function<void(Magic::Wizard&, Magic::Wizard&)>, int> > > playerPendings;
	int loopValue;

public:
	void incertInPendings(Magic::Wizard& attacker, int round, std::function<void(Magic::Wizard&, Magic::Wizard&)> action);
	int getRoundNum();
	void nextRound();
	Magic::Wizard* getTurn();
	void nextTurn(Magic::Wizard& player);
	void fulfillPendings(Magic::Wizard&, Magic::Wizard&);
	Round& operator+(int);
	Round& operator-(int);
	void operator+(std::function<void(Magic::Wizard&, Magic::Wizard&)>);
};
#endif