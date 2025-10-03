#include "Player.h"
#include "Utils.h"
#include <iostream>

Player::Player(CharacterClass startClass) {
	initNewPlayer(startClass);
}

void Player::initNewPlayer(CharacterClass startClass) {
	name = "Player";
	strength = getRandom(1, 3);
	dexterity = getRandom(1, 3);
	endurance = getRandom(1, 3);
	classLvl.clear();
	classLvl[startClass] = 1;
	applyStatBonus();
}

void Player::applyStatBonus() {
	int bonusstr = 0, bonusdex = 0, bonusend = 0;
	int basehp = 0;

	//start baff
	if (classLvl[CharacterClass::ROGUE] >= 2) bonusdex += 1;
	if (classLvl[CharacterClass::WARRIOR] >= 3) bonusdex += 1;
	if (classLvl[CharacterClass::BARBARIAN] >= 3) bonusdex += 1;

	strength += bonusstr;
	dexterity += bonusdex;
	endurance += bonusend;

	if (currentWeapon.name.empty()) {
		if (classLvl.count(CharacterClass::ROGUE)) {
			currentWeapon = { "Dagger", 2, DamageType::PIERCING, WeaponType::DAGGER };

		}
		else if (classLvl.count(CharacterClass::WARRIOR)) {
			currentWeapon = { "Sword", 3, DamageType::SLASHING, WeaponType::SWORD };
		}
		else {
			currentWeapon = { "Club", 3, DamageType::BLUDGEONING, WeaponType::CLUB };
		}
	}

	for (auto const& [key, val] : classLvl) {
		if (val > 0) {
			if (key == CharacterClass::ROGUE) basehp += 4 * val;
			if (key == CharacterClass::WARRIOR) basehp += 5 * val;
			if (key == CharacterClass::BARBARIAN) basehp += 6 * val;
		}

		maxhp = basehp + endurance;
		hp = maxhp;
	}
}

void Player::lvlup(CharacterClass choice) {
	if (getTotallvl() < 3) {
		classLvl[choice]++;
		applyStatBonus();
		std::cout << "Lvl UP! You are: ";
		for (auto const& [key, val] : classLvl) {
			if (val > 0) {
				std::string className;
				if (key == CharacterClass::ROGUE) className = "ROGUE";
				if (key == CharacterClass::WARRIOR) className = "Warrior";
				if (key == CharacterClass::BARBARIAN) className = "Barbarian";
				std::cout << className << " " << val << " ";
			}
		}
		std::cout << std::endl;
	}
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
	for (auto const& [key, val] : classLvl) {
		total += val;
	}
	return total;
}

int Player::calcBaseDamage(Obj_game& targer) {
	return currentWeapon.damage + strength;
}

int Player::applyDamageMode(int baseDamage, Obj_game& target, int turn) {
	int modifDmg = baseDamage;

	// ROGUE 1
	if (classLvl[CharacterClass::ROGUE] >= 1 && dexterity > target.getdexterity()) {
		modifDmg += 1;
	}

	// ROGUE 3
	if (classLvl[CharacterClass::ROGUE] >= 3 && turn > 1) {
		poisonDamageCount++;
		modifDmg += poisonDamageCount;
	}

	// warrior 1
	if (classLvl[CharacterClass::WARRIOR] >= 1 && turn == 1) {
		modifDmg += currentWeapon.damage;
	}
	// barbarian 1
	if (classLvl[CharacterClass::BARBARIAN] >= 1) {
		if (turn <= 3) modifDmg += 2;
		else modifDmg -= 1;
	}

	return modifDmg;
}

void Player::takeModeDamage(int incomingDmg, Obj_game& attaker, int turn) {
	int finalDmg = incomingDmg;

	//warrior 2
	if (classLvl[CharacterClass::WARRIOR] >= 2 && strength > attaker.getstrength()) {
		finalDmg -= 3;
	}

	// barbarian 2
	if (classLvl[CharacterClass::BARBARIAN] >= 2) {
		finalDmg -= endurance;
	}

	takeDamage(finalDmg);
}