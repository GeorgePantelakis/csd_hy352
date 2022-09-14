#ifndef MAGIC_H
#define MAGIC_H
#include <iostream>
#include <vector>
#include <map>
#include <functional>

namespace Magic{
	class Spell;

	class Wizard {
	public:
		static std::map<std::string, Magic::Wizard> getWizards();

		Wizard(std::string, std::string, int);
		Wizard(const Wizard&);
		std::string getName() const;
		std::string getHouse() const;
		double getMaxHP() const;
		double getHP() const;
		bool hasWand() const;
		bool live() const;
		bool isOddRound() const;
		std::map<std::string, Magic::Spell> getSpells() const;
		void equipWand(bool);
		void getDamage(double);
		void getHeal(double);
		void setOpponentHouse(std::string);
		void castSpell(Magic::Spell, Wizard&);
		void changeRoundFlag();
		void setPlayerNum(int);
		int getPlayerNum();
		Wizard operator,(Wizard);
		void operator[](Wizard);
		void operator[](std::string);
		Wizard& operator-();
		Wizard operator+(int);
		void operator+(bool value);

	private:
		static std::map<std::string, Magic::Wizard> wizards;

		const std::string wizardName;
		const std::string house;
		double hp;
		const double maxHP;
		bool wandEquip;
		bool isAlive;
		std::map<std::string, Magic::Spell> spells;
		int playerNum = 0;
		std::string opponentHouse;
		bool oddRound;
	
		void addSpells(std::map<std::string, Magic::Spell>);
		void learnSpell(Magic::Spell);
	};

	class Spell {
	private:
		static std::map<std::string, Magic::Spell> spells;

		const std::string spellName;
		std::function<void(Magic::Wizard&, Magic::Wizard&)> action;

	public:
		static std::map<std::string, Magic::Spell> getSpells();

		Spell(std::string, std::function<void(Magic::Wizard&, Magic::Wizard&)>);
		Spell(const Spell&);
		std::string getName() const;
		std::function<void(Magic::Wizard&, Magic::Wizard&)> getAction() const;
		Spell operator,(Spell);
		void operator[](Spell);
		Spell& operator= (const Spell&);
	};
}
#endif