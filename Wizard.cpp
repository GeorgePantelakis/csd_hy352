#include "Magic.h"

#define UNKNOWN_HOUSE 0
#define UNKNOWN_SPELL 1

std::map<std::string, Magic::Wizard> Magic::Wizard::wizards;

std::map<std::string, Magic::Wizard> Magic::Wizard::getWizards()
{
	return Magic::Wizard::wizards;
}

void Magic::Wizard::learnSpell(Magic::Spell newSpell)
{
	if (spells.find(newSpell.getName()) == spells.end())
		spells.insert(std::pair<std::string, Magic::Spell>(newSpell.getName(), newSpell));
}

void Magic::Wizard::addSpells(std::map<std::string, Magic::Spell> _spells)
{
	for (std::pair<std::string, Magic::Spell> spell : _spells)
		if (spells.find(spell.first) == spells.end())
			spells.insert(spell);
}

Magic::Wizard::Wizard(std::string _name, std::string _house, int _hp): wizardName(_name), house(_house), maxHP(_hp)
{
	hp = maxHP;
	wandEquip = true;
	isAlive = true;
	oddRound = true;

	try {
		if (house.compare("dummy")
			&& house.compare("Gryffindor")
			&& house.compare("Slytherin")
			&& house.compare("Hufflepuff")
			&& house.compare("Ravenclaw"))
			throw UNKNOWN_HOUSE;
	}
	catch (...) {
		std::cerr << "Error in CREATE WIZARD (NAME: \"" << wizardName << "\"). Invalid HOUSE." << std::endl
			<< "Choices are: \"Gryffindor\", \"Slytherin\", \"Hufflepuff\", \"Ravenclaw\"";
		exit(EXIT_FAILURE);
	}

	if (wizardName.compare("dummy") && Magic::Wizard::wizards.find(wizardName) == Magic::Wizard::wizards.end())
		Magic::Wizard::wizards.insert(std::pair<std::string, Magic::Wizard>(wizardName, *this));
}

Magic::Wizard::Wizard(const Magic::Wizard& wizard): wizardName(wizard.getName()), house(wizard.getHouse()), maxHP(wizard.getMaxHP())
{
	hp = wizard.getHP();
	wandEquip = wizard.hasWand();
	isAlive = wizard.live();
	spells = wizard.getSpells();
	oddRound = wizard.isOddRound();
}

std::string Magic::Wizard::getName() const
{
	return wizardName;
}

std::string Magic::Wizard::getHouse() const
{
	return house;
}

double Magic::Wizard::getMaxHP() const
{
	return maxHP;
}

double Magic::Wizard::getHP() const
{
	return hp;
}

bool Magic::Wizard::hasWand() const
{
	return wandEquip;
}

bool Magic::Wizard::live() const
{
	return isAlive;
}

bool Magic::Wizard::isOddRound() const
{
	return oddRound;
}

std::map<std::string, Magic::Spell> Magic::Wizard::getSpells() const
{
	return spells;
}

void Magic::Wizard::equipWand(bool equip)
{
	wandEquip = equip;
}

void Magic::Wizard::getDamage(double damage)
{
	if(hp - damage > 0)	
		hp -= damage;
	else {
		hp = 0;
		isAlive = false;
	}
}

void Magic::Wizard::getHeal(double heal)
{
	if (hp + heal < maxHP)
		hp += heal;
	else
		hp = maxHP;
}

void Magic::Wizard::setOpponentHouse(std::string _opponentHouse)
{
	opponentHouse = _opponentHouse;
}

void Magic::Wizard::castSpell(Magic::Spell spell, Magic::Wizard& defender)
{
	if (wandEquip) {
		try {
			if (spells.find(spell.getName()) != spells.end()) {
				defender.setOpponentHouse(house);
				opponentHouse = defender.getHouse();
				spell.getAction()(*this, defender);
			}
			else
				throw UNKNOWN_SPELL;
		}
		catch (int err) {
			if(err == UNKNOWN_SPELL)
				std::cerr << "Error when wizard with name: \"" << wizardName << "\" cast a spell."
					"Wizard doesn't know spell with name: \"" << spell.getName() << "\"." << std::endl;
		}
	}
	
}

void Magic::Wizard::changeRoundFlag()
{
	oddRound = !oddRound;
}

void Magic::Wizard::setPlayerNum(int _playerNum) {
	playerNum = _playerNum;
}

int Magic::Wizard::getPlayerNum() {
	return playerNum;
}

Magic::Wizard Magic::Wizard::operator,(Magic::Wizard wizard)
{
	return Wizard{ wizard };
}

void Magic::Wizard::operator[](Magic::Wizard wizard)
{
	return;
}

void Magic::Wizard::operator[](std::string spellsNames)
{
	// split spellsName with " " as delimiter
	std::vector<std::string> names;
	size_t pos = 0;
	std::string token;
	while ((pos = spellsNames.find(" ")) != std::string::npos) {
		token = spellsNames.substr(0, pos);
		names.push_back(token);
		spellsNames.erase(0, pos + 1);
	}
	
	std::map<std::string, Magic::Spell> allSpells = Magic::Spell::getSpells();
	for (std::string name : names) {
		try {
			std::map<std::string, Magic::Spell>::iterator spellIt = allSpells.find(name);
			if (spellIt != allSpells.end())
				learnSpell(spellIt->second);
			else
				throw UNKNOWN_SPELL;
		}
		catch (...) {
			std::cerr << "Error in SPELL_NAME. Spell with name: \"" << name << "\" doesn't exist." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	Magic::Wizard::wizards.at(wizardName).addSpells(spells);
}

Magic::Wizard& Magic::Wizard::operator-()
{
	hp = -hp;
	return *this;
}

Magic::Wizard Magic::Wizard::operator+(int iValue)
{
	double dValue = iValue;
	if (hp < 0) {
		hp = abs(hp);
		if(!house.compare("Gryffindor"))
			if(!opponentHouse.compare("Slytherin")) {
				dValue *= 1.2;
				dValue *= 0.7;
			}
			else
				dValue *= 0.8;
		else if(!house.compare("Hufflepuff"))
			dValue *= 0.93;
		
		if(!opponentHouse.compare("Slytherin") && house.compare("Gryffindor")) dValue *= 1.15;
		else if(!opponentHouse.compare("Hufflepuff")) dValue *= 1.07;
		else if(!opponentHouse.compare("Ravenclaw") && oddRound) dValue *= 1.07;
		getDamage(dValue);
	} else
		getHeal(dValue);

	return *this;
}

void Magic::Wizard::operator+(bool value)
{
	equipWand(value);
}