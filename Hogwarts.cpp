#include "Hogwarts.h"

Magic::Wizard findWizard(std::map<std::string, Magic::Wizard> wizards, std::string wizardName)
{
	try {
		std::map<std::string, Magic::Wizard>::iterator wizardIt = wizards.find(wizardName);
		if (wizardIt == wizards.end())
			throw 1;

		return wizardIt->second;
	}
	catch (...) {
		std::cerr << "Error in LEARN. Wizard with name: \"" << wizardName << "\" doesn't exist." << std::endl;
		exit(EXIT_FAILURE);
	}
}

bool operator--(WandValue value)
{
	return static_cast<bool>(value);
}

WandValue& operator-(WandValue value)
{
	return value;
}

void gameLoop(Round& round) {
	std::cout << "-------------------------------------HARRY POTTER THE GAME-------------------------------------" << std::endl << std::endl;

	std::string temp;
	std::map<std::string, Magic::Wizard> wizards = Magic::Wizard::getWizards();
	
	std::cout << "Player1 select wizard:\n----------------------------" << std::endl;
	for (std::pair<std::string, Magic::Wizard> wizard : wizards) {
		std::cout << "\033[1; 32m" << wizard.first << "\033[0m" << std::endl;
	}
	std::cout << "----------------------------" << std::endl;
	getline(std::cin, temp);
	while (wizards.find(temp) == wizards.end()) {
		std::cout << "There is no wizard with name \"" << temp << "\". Please try again" << std::endl;
		getline(std::cin, temp);
	}
	Magic::Wizard player1{ wizards.find(temp)->second };
	player1.setPlayerNum(1);

	std::cout << std::endl << "Player2 select wizard:\n----------------------------" << std::endl;
	for (std::pair<std::string, Magic::Wizard> wizard : wizards) {
		std::cout << "\033[1; 32m" << wizard.first << "\033[0m" << std::endl;
	}
	std::cout << "----------------------------" << std::endl;
	getline(std::cin, temp);
	while (wizards.find(temp) == wizards.end()) {
		std::cout << "There is no wizard with name \"" << temp << "\". Please try again" << std::endl;
		getline(std::cin, temp);
	}
	Magic::Wizard player2{ wizards.find(temp)->second };
	player2.setPlayerNum(2);

	std::map<std::string, Magic::Spell> player1Spells = player1.getSpells();
	std::map<std::string, Magic::Spell> player2Spells = player2.getSpells();

	while (player1.live() && player2.live()) {
		std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl << "Round " << round.getRoundNum() << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

		if (!player1.getHouse().compare("Ravenclaw") && round.getRoundNum() % 2 == 0) player1.getHeal(player1.getMaxHP() * 0.05);
		if (!player2.getHouse().compare("Ravenclaw") && round.getRoundNum() % 2 == 0) player2.getHeal(player2.getMaxHP() * 0.05);
		round.nextTurn(player1);

		if (player1.hasWand()) {
			std::cout << player1.getName() << "(Player1) select spell:\n----------------------------" << std::endl;
			for (std::pair<std::string, Magic::Spell> spell : player1Spells) {
				std::cout << "\033[4; 36m" << spell.first << "\033[0m" << std::endl;
			}
			std::cout << "----------------------------" << std::endl;
			getline(std::cin, temp);
			while (player1Spells.find(temp) == player1Spells.end()) {
				std::cout << "Wizard doesn\' know the spell with name \"" << temp << "\". Please try again" << std::endl;
				getline(std::cin, temp);
			}
			player1.castSpell(player1Spells.find(temp)->second, player2);

			round.fulfillPendings(player1, player2);

			printStatus(player1, player2);
		}
		else {
			round.fulfillPendings(player1, player2);
			std::cout << player1.getName() << "(Player1) has not a wand so he can\'t cast a spell." << std::endl;
		}
		std::cout << std::endl;
		
		if (!player1.live() || !player2.live()) break;

		round.nextTurn(player2);

		if (player2.hasWand()) {
			std::cout << player2.getName() << "(Player2) select spell:\n----------------------------" << std::endl;
			for (std::pair<std::string, Magic::Spell> spell : player2Spells) {
				std::cout << spell.first << std::endl;
			}
			std::cout << "----------------------------" << std::endl;
			getline(std::cin, temp);
			while (player2Spells.find(temp) == player2Spells.end()) {
				std::cout << "Wizard doesn\' know the spell with name \"" << temp << "\". Please try again" << std::endl;
				getline(std::cin, temp);
			}
			player2.castSpell(player2Spells.find(temp)->second, player1);

			round.fulfillPendings(player2, player1);

			printStatus(player1, player2);
		}
		else {
			round.fulfillPendings(player2, player1);
			std::cout << player2.getName() << "(Player2) has not a wand so he can\'t cast a spell." << std::endl;
		}
		std::cout << std::endl;

		round.nextRound();
		player1.changeRoundFlag();
		player2.changeRoundFlag();
	}

	if (player1.live())
		std::cout << "Winner is \"" << player1.getName() << "\"(Player 1)" << std::endl;
	else
		std::cout << "Winner is \"" << player2.getName() << "\"(Player 2)" << std::endl;
}

void printStatus(Magic::Wizard player1, Magic::Wizard player2) {
	std::cout << std::endl;
	std::cout << "############################" << std::endl;
	std::cout << "Name: " << player1.getName() << std::endl;
	std::cout << "HP: " << player1.getHP() << std::endl;
	std::cout << "Wand " << (player1.hasWand() ? "equipped" : "not equipped") << std::endl;
	std::cout << "############################" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "############################" << std::endl;
	std::cout << "Name: " << player2.getName() << std::endl;
	std::cout << "HP: " << player2.getHP() << std::endl;
	std::cout << "Wand " << (player2.hasWand() ? "equipped" : "not equipped") << std::endl;
	std::cout << "############################" << std::endl;
	std::cout << std::endl;
}