#include "Monster.h"
#include "Utils.h"
#include "TypeRegistry.h"

void Monster::takeModeDamage(int incomingDamage, Obj_game& attaker) {
	takeDamage(incomingDamage);
}

Goblin::Goblin() {
	name = "Goblin"; hp = 5; maxhp = 5; strength = 1; dexterity = 1; endurance = 1;
	currentWeapon = { "rusty knife", 2, &TypeRegisrtry::getPiercing(), &TypeRegisrtry::getDagger()};
	loot = { "dagger", 2, &TypeRegisrtry::getPiercing(), &TypeRegisrtry::getDagger()};
}

Skeleton::Skeleton() {
	name = "Skeleten"; hp = 10; maxhp = 10; strength = 2; dexterity = 2; endurance = 1;
	currentWeapon = { "bone sword", 2, &TypeRegisrtry::getSlashing(), &TypeRegisrtry::getSword() };
	loot = { "club", 3, &TypeRegisrtry::getBludgeoning(), &TypeRegisrtry::getClub() };
}

Slime::Slime() {
	name = "Slime"; hp = 8; maxhp = 8; strength = 3; dexterity = 1; endurance = 2;
	currentWeapon = { "acid spit", 1, &TypeRegisrtry::getPiercing(), &TypeRegisrtry::getSpear() };
	loot = { "acid spit", 3, &TypeRegisrtry::getPiercing(), &TypeRegisrtry::getSpear() };
}

Ghost::Ghost() {
	name = "Ghost"; hp = 6; maxhp = 6; strength = 1; dexterity = 3; endurance = 1;
	currentWeapon = { "touch of horror", 3, &TypeRegisrtry::getSlashing(), &TypeRegisrtry::getSword() };
	loot = { "sword", 3, &TypeRegisrtry::getSlashing(), &TypeRegisrtry::getSword() };
}

Golem::Golem() {
	name = "Golem"; hp = 10; maxhp = 10; strength = 3; dexterity = 1; endurance = 3;
	currentWeapon = { "stone fist", 1, &TypeRegisrtry::getBludgeoning(), &TypeRegisrtry::getClub() };
	loot = { "axe", 4, &TypeRegisrtry::getSlashing(), &TypeRegisrtry::getAxe() };
}

Dragon::Dragon() {
	name = "Dragon"; hp = 20; maxhp = 20; strength = 3; dexterity = 3; endurance = 3;
	currentWeapon = { "bite", 4, &TypeRegisrtry::getPiercing(), &TypeRegisrtry::getSpear() };
	loot = { "legendary sword", 10, &TypeRegisrtry::getSlashing(), &TypeRegisrtry::getLegendarySword() };
}

void Skeleton::takeModeDamage(int incomingDamage, Obj_game& attaker) {
	int finalDmg = incomingDamage;
	if (attaker.getweapon().damage_type == &TypeRegisrtry::getBludgeoning()) {
		finalDmg *= 2;
	}
	takeDamage(finalDmg);
}

void Slime::takeModeDamage(int incomingDamage, Obj_game& attaker) {
	int finalDmg = incomingDamage;
	if (attaker.getweapon().damage_type == &TypeRegisrtry::getSlashing()) {
		finalDmg *= strength;
	}
	takeDamage(finalDmg);
}

int Ghost::applyDamageMode(int baseDamage, int turn) {
	return baseDamage + 1;
}

void Golem::takeModeDamage(int incomingDamage, Obj_game& attaker) {
	takeDamage(incomingDamage - endurance);
}

int Dragon::applyDamageMode(int baseDamage, int turn) {
	if (turn % 3 == 0) {
		return baseDamage + 3;
	}
	return baseDamage;
}

std::unique_ptr<Monster> MonsterFactory::createRandomMonster() {
	int type = getRandom(0, 5);
	switch (type) {
		case 0: return std::make_unique<Goblin>();
		case 1: return std::make_unique<Skeleton>();
		case 2: return std::make_unique<Slime>();
		case 3: return std::make_unique<Ghost>();
		case 4: return std::make_unique<Golem>();
		case 5: return std::make_unique<Dragon>();
		default: return std::make_unique<Goblin>();
	}
}


