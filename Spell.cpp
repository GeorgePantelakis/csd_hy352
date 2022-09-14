#include "Magic.h"

std::map<std::string, Magic::Spell> Magic::Spell::spells;

std::map<std::string, Magic::Spell> Magic::Spell::getSpells()
{
	return Magic::Spell::spells;
}

Magic::Spell::Spell(std::string name, std::function<void(Magic::Wizard&, Magic::Wizard&)> action): spellName(name), action(action)
{
	if (spellName.compare("dummy") && Magic::Spell::spells.find(spellName) == Magic::Spell::spells.end())
		Magic::Spell::spells.insert(std::pair<std::string, Magic::Spell>(spellName, *this));
}

Magic::Spell::Spell(const Magic::Spell& spell) : spellName(spell.getName()), action(spell.getAction()){}

std::string Magic::Spell::getName() const
{
	return spellName;
}

std::function<void(Magic::Wizard&, Magic::Wizard&)> Magic::Spell::getAction() const 
{
	return action;
}

Magic::Spell Magic::Spell::operator,(Magic::Spell spell)
{
	return Spell{ spell.getName(), spell.getAction() };
}

void Magic::Spell::operator[](Magic::Spell spell)
{
	return;
}

Magic::Spell& Magic::Spell::operator= (const Magic::Spell &spell)
{
	Spell copySpell{ spell };

	return copySpell;
}