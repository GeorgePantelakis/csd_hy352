#include "Round.h"

void Round::incertInPendings(Magic::Wizard& attacker, int round, std::function<void(Magic::Wizard&, Magic::Wizard&)> action)
{
	if (playerPendings.find(attacker.getPlayerNum()) == playerPendings.end())
		playerPendings.insert({ attacker.getPlayerNum(), {{ action, round }} });
	else
		playerPendings.at(attacker.getPlayerNum()).push_back({ action, round });
}

int Round::getRoundNum() {
	return roundNum;
}

void Round::nextRound() {
	roundNum-=-1;
}

Magic::Wizard* Round::getTurn() {
	return turn;
}

void Round::nextTurn(Magic::Wizard& player) {
	turn = &player;
}

void Round::fulfillPendings(Magic::Wizard& attacker, Magic::Wizard& defender) {
	if(playerPendings.find(attacker.getPlayerNum()) != playerPendings.end())
		for (std::pair<std::function<void(Magic::Wizard&, Magic::Wizard&)>, int> value : playerPendings.at(attacker.getPlayerNum()))
			if (value.second == roundNum)
				value.first(attacker, defender);
}

Round& Round::operator+(int value) {
	loopValue = value;
	return *this;
}

Round& Round::operator-(int value) {
	loopValue = -value;
	return *this;
}

void Round::operator+(std::function<void(Magic::Wizard&, Magic::Wizard&)> action) {
	if(loopValue > 0)
		for (int i = roundNum; i < roundNum + loopValue; ++i)
			incertInPendings(*turn, i, action);
	else
		incertInPendings(*turn, roundNum  + abs(loopValue), action);
	loopValue = 0;
}