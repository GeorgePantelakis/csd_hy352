#ifndef HOGWARTS_H
#define HOGWARTS_H
#include "Round.h"
#include "Magic.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

//~~~~~~Defines~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define BEGIN_GAME int main(void) { \
						Magic::Wizard tmpWiz{"dummy", "dummy", -1};\
						Magic::Spell tmpSpell{"dummy", {[](Magic::Wizard &a, Magic::Wizard &d){}}};\
						std::function<void(Magic::Wizard&, Magic::Wizard&)> foo;\
						Round round;
#define END_GAME return EXIT_SUCCESS;}
#define CREATE ;
#define WIZARD Magic::Wizard
#define WIZARDS tmpWiz
#define SPELL Magic::Spell
#define SPELLS tmpSpell
#define DAMAGE ;-
#define HEAL ;
#define EQUIP ;
#define GET_HOUSE(X) (X 0).getHouse()
#define GET_HP(X) (X 0).getHP()
#define GET_NAME(X) (X 0).getName()
#define HAS_WAND(X) (X 0).hasWand()
#define ATTACKER attacker +
#define DEFENDER defender +
#define SHOW ;std::cout <<
#define NAME false ? ""
#define HOUSE false ? ""
#define HP false ? 0
#define ACTION false ? foo
#define START [&](Magic::Wizard &attacker, Magic::Wizard &defender) {
#define IF if(
#define DO ){
#define ELSE_IF ;}else if(
#define ELSE ;}else{
#define FOR ;(round +
#define AFTER ;(round -
#define ROUNDS ) + [](Magic::Wizard &attacker, Magic::Wizard &defender
#define END ;}
#define DUEL ; gameLoop(round);
#define AND(a, b, ...) [&](decltype(b))->bool{ std::vector<bool> exps{a, b, __VA_ARGS__}; bool exp = true; for(bool val : exps) exp = exp && val; return exp; }(b)
#define OR(a, b, ...) [&](decltype(b))->bool{ std::vector<bool> exps{a, b, __VA_ARGS__}; bool exp = false; for(bool val : exps) exp = exp || val; return exp; }(b)
#define NOT(a) !(a)
#define MR ; findWizard(Magic::Wizard::getWizards(),
#define MRS ; findWizard(Magic::Wizard::getWizards(),
#define LEARN )
#define SPELL_NAME(spellName) #spellName " "

//~~~~~~Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enum WandValue {
	α = true
};

extern WandValue& operator-(WandValue value);
extern bool operator--(WandValue value);

extern Magic::Wizard findWizard(std::map<std::string, Magic::Wizard>, std::string);
extern void gameLoop(Round&);
extern void printStatus(Magic::Wizard, Magic::Wizard);

//~~~~~~Global Variables~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const bool _ = false;
#endif