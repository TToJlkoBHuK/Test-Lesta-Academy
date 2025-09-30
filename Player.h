#pragma once
#include "obj_game.h"
#include "Enum.h"
#include <map>

class Player : public Obj_game {
public:
	Player(CharacterClass startClass);
	void lvlup(CharacterClass choise);
	void equipWeapon(const Weapon& newWeapon);
	void fullheal();
	int getTotallvl() const;

	//fight logical
	int calcBaseDamage(Obj_game& target);
	int applyDamageMode(int baseDamage, Obj_game& target, int turn);
	void takeModeDamage(int incomingDamge, Obj_game& target, int turn);

private:
	void initNewPlayer(CharacterClass startClass);
	void applyStatBonus();

	std::map<CharacterClass, int> classLvl;
	int poisonDamageCount = 0; //rouge
};