#include "CharacterClass.h"
#include "Player.h"
#include "Utils.h"

// Rouge

Weapon Rouge::getStartWeapon() const {
	return { "Dagger", 2, &TypeRegisrtry::getPiercing(), &TypeRegisrtry::getDagger()};
}

int Rouge::applyDmgBonus(int currentDmg, int lvl, Player& player, Obj_game& target, int turn) const {
	int modDmg = currentDmg;
	if (lvl >= 1 && player.getdexterity() > target.getdexterity()) {
		modDmg += 1;
	}
	if (lvl >= 3 && turn > 1) {
		modDmg += player.incrementAndGetPoisionCount();
	}
	return modDmg;
}

int Rouge::applyDefBonus(int incomingDamage, int lvl, Player& player, Obj_game& attaker, int turn) const {
	return incomingDamage;
}

void Rouge::applyStatBonus(int lvl, int& str, int& dex, int& end) const {
	if (lvl >= 2) dex += 1;
}

Weapon Warrior::getStartWeapon() const {
	return { "Sword", 3, &TypeRegisrtry::getSlashing(), &TypeRegisrtry::getSword() };
}

int Warrior::applyDmgBonus(int currentDamage, int level, Player& player, Obj_game& target, int turn) const {
	if (level >= 1 && turn == 1) {
		return currentDamage + player.getweapon().damage;
	}
	return currentDamage;
}

int Warrior::applyDefBonus(int incomingDamage, int lvl, Player& player, Obj_game& attaker, int turn) const {
	if (lvl >= 2 && player.getstrength() > attaker.getstrength()) {
		return incomingDamage = 3;
	}
	return incomingDamage;
}

void Warrior::applyStatBonus(int lvl, int& str, int& dex, int& end) const {
	if (lvl >= 3) dex += 1;
}

Weapon Barbarian::getStartWeapon() const {
	return { "Club", 3, &TypeRegisrtry::getSlashing(), &TypeRegisrtry::getClub() };
}

int Barbarian::applyDmgBonus(int currentDamage, int lvl, Player& player, Obj_game& target, int turn) const {
	if (lvl >= 1) {
		if (turn <= 3) return currentDamage + 2;
		else return currentDamage - 1;
	}
	return currentDamage;
}

int Barbarian::applyDefBonus(int incomingDamage, int lvl, Player& player, Obj_game& attaker, int turn) const {
	if (lvl >= 2) {
		return incomingDamage - player.getendurance();
	}
	return incomingDamage;
}

void Barbarian::applyStatBonus(int lvl, int& str, int& dex, int& end) const {
	if (lvl >= 3) dex += 1;
}

std::unique_ptr<CharacterClass> CharacterClassFactory::create(const std::string& className) {
	if (className == "Rouge") return std::make_unique<Rouge>();
	if (className == "Warrior") return std::make_unique<Warrior>();
	if (className == "Barbarian") return std::make_unique<Barbarian>();
	return nullptr;
}