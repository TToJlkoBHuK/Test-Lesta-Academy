#pragma once
#include "obj_game.h"
#include "CharacterClass.h"
#include <map>
#include <string>

class Player : public Obj_game {
public:
	Player(std::unique_ptr<CharacterClass> startClass);
	void lvlup(const std::string& className);
	void equipWeapon(const Weapon& newWeapon);
	void fullheal();
	int getTotallvl() const;
	int incrementAndGetPoisionCount() { return ++poisonDamageCount; }

	//fight logical
	int calcBaseDamage(Obj_game& target);
	int applyDamageMode(int baseDamage, Obj_game& target, int turn);
	void takeModeDamage(int incomingDamge, Obj_game& target, int turn);

private:
	void applyAllBonus();
	std::map<std::string, std::pair<std::unique_ptr<CharacterClass>, int>> classLvl;

	int baseStrenght = 0;
	int baseDexterity = 0;
	int baseEndurance = 0;
	int poisonDamageCount = 0; //ROGUE
};