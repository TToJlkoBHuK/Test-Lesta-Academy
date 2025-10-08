#include "Player.h"
#include "Utils.h"
#include <iostream>

Player::Player(std::unique_ptr<CharacterClass> startClass) {
	name = "Player";
	baseStrenght = getRandom(1, 3);
	baseDexterity = getRandom(1, 3);
	baseEndurance = getRandom(1, 3);

	std::string className = startClass->getName();
	currentWeapon = startClass->getStartWeapon();
	classLvl[className] = {std::move(startClass), 1};

	applyAllBonus();
}

void Player::applyAllBonus() {
	strength = baseStrenght;
	dexterity = baseDexterity;
	endurance = baseEndurance;
	int bonusStr = 0, bonusDex = 0, bonusEnd = 0, baseHp = 0;

	for (auto const& [name, data] : classLvl) {
		const auto& [classPtr, lvl] = data;
		classPtr->applyStatBonus(lvl, bonusStr, bonusDex, bonusEnd);
		baseHp += classPtr->getBaseHPLvl() * lvl;
	}

	strength += bonusStr;
	dexterity += bonusDex;
	endurance += bonusEnd;

	maxhp = baseHp + endurance;
	hp = maxhp;
}

void Player::lvlup(const std::string& className) {
	if (getTotallvl() >= 3) return;

	if (classLvl.count(className)) {
		classLvl[className].second++;
	}
	else {
		auto newClass = CharacterClassFactory::create(className);
		if (newClass) {
			classLvl[className] = { std::move(newClass), 1 };
		}
	}

	applyAllBonus();

	std::cout << "Lvl UP! You are: ";
	for (auto const& [name, data] : classLvl) {
		std::cout << name << " " << data.second << " ";
	}
	std::cout << std::endl;
}

void Player::equipWeapon(const Weapon& newWeapon) {
	currentWeapon = newWeapon;
}

void Player::fullheal() {
	hp = maxhp;
	poisonDamageCount = 0;
}

int Player::getTotallvl() const {
	int total = 0;
	for (auto const& [name, data] : classLvl) {
		total += data.second;
	}
	return total;
}

int Player::calcBaseDamage(Obj_game& targer) {
	return currentWeapon.damage + strength;
}

int Player::applyDamageMode(int baseDamage, Obj_game& target, int turn) {
	int modifDmg = baseDamage;
	for (auto const& [name, data] : classLvl) {
		const auto& [classPtr, lvl] = data;
		modifDmg = classPtr->applyDmgBonus(modifDmg, lvl, *this, target, turn);
	}

	return modifDmg;
}

void Player::takeModeDamage(int incomingDmg, Obj_game& attaker, int turn) {
	int finalDmg = incomingDmg;
	for (auto const& [name, data] : classLvl) {
		const auto& [classPtr, lvl] = data;
		finalDmg = classPtr->applyDefBonus(finalDmg, lvl, *this, attaker, turn);
	}

	takeDamage(finalDmg);
}