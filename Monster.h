#pragma once
#include "obj_game.h"

class Monster : public Obj_game {
public:
	Monster(MonsterType type);
	Weapon getloot() const { return loot; }

	//fight logical
	int calcBaseDamage();
	int applyDamageMode(int baseDamage, int turn);
	void takeModeDamage(int incomingDamage, Obj_game& attack);

private:
	MonsterType MonsterType;
	Weapon loot;
};