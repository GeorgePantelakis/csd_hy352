#include "Hogwarts.h"

BEGIN_GAME
	CREATE SPELL{
		NAME: "Expelliarmus",
		ACTION : START
			EQUIP DEFENDER _
			AFTER 2 ROUNDS DO
				EQUIP DEFENDER-- - α
			END
			END
	}

	CREATE SPELL{
		NAME: "Sectumsempra",
		ACTION : START
			FOR 5 ROUNDS DO
				DAMAGE DEFENDER 8
			END
		END
	}

	CREATE SPELL{
		NAME: "Expulso",
		ACTION : START
			DAMAGE DEFENDER 22
		END
	}

	CREATE SPELL{
		NAME: "Anapneo",
		ACTION : START
			HEAL ATTACKER 30
		END
	}

	CREATE WIZARD{
		NAME: "Harry Potter",
		HOUSE : "Gryffindor",
		HP : 100
	}

	CREATE WIZARD{
		NAME: "Draco Malfoy",
		HOUSE : "Slytherin",
		HP : 90
	}

	MR "Harry Potter" LEARN[
		SPELL_NAME(Expelliarmus)
		SPELL_NAME(Sectumsempra)
		SPELL_NAME(Expulso)
		SPELL_NAME(Anapneo)
	]

	MR "Draco Malfoy" LEARN[
		SPELL_NAME(Expelliarmus)
		SPELL_NAME(Expulso)
	]

	DUEL

END_GAME