#include "Monster.h"

Monster::Monster(MonsterType type) : monsterType(type) {
	switch (type) {
		case MonsterType::GOBLIN:
			name = "Goblin"; hp = 5; maxhp = 5; strength = 1; dexterity = 1; endurance = 1; 
			currentWeapon = { "rusty knife", 2, DamageType::PIERCING, WeaponType::DAGGER };
			loot = { "dagger", 2, DamageType::PIERCING, WeaponType::DAGGER };
			break;
		case MonsterType::SKELETEN:
			name = "Skeleten"; hp = 10; maxhp = 10; strength = 2; dexterity = 2; endurance = 1;
			currentWeapon = { "bone sword", 2, DamageType::SLASHING, WeaponType::SWORD };
			loot = { "club", 3, DamageType::BLUDGEONING, WeaponType::CLUB };
			break;
		case MonsterType::SLIME:
			name = "Slime"; hp = 8; maxhp = 8; strength = 3; dexterity = 1; endurance = 2;
			currentWeapon = { "acid spit", 1, DamageType::PIERCING, WeaponType::SPEAR };
			loot = { "acid spit", 3, DamageType::PIERCING, WeaponType::SPEAR };
			break;
		case MonsterType::GHOST:
			name = "Ghost"; hp = 6; maxhp = 6; strength = 1; dexterity = 3; endurance = 1;
			currentWeapon = { "touch of horror", 3, DamageType::SLASHING, WeaponType::SWORD };
			loot = { "sword", 3, DamageType::SLASHING, WeaponType::SWORD };
			break;
		case MonsterType::GOLEM:
			name = "Golem"; hp = 10; maxhp = 10; strength = 3; dexterity = 1; endurance = 3;
			currentWeapon = { "stone fist", 1, DamageType::BLUDGEONING, WeaponType::CLUB };
			loot = { "axe", 4, DamageType::SLASHING, WeaponType::AXE };
			break;
		case MonsterType::DRAGON:
			name = "Dragon"; hp = 20; maxhp = 20; strength = 3; dexterity = 3; endurance = 3;
			currentWeapon = { "bite", 4, DamageType::PIERCING, WeaponType::SPEAR };
			loot = { "legendary sword", 10, DamageType::SLASHING, WeaponType::LEGENDARY_SWORD };
			break;
	}
}

int Monster::calcBaseDamage() {
	return currentWeapon.damage + strength;
}

int Monster::applyDamageMode(int baseDmg, int turn) {
	int modDmg = baseDmg;

	//Ghost
	if (monsterType == MonsterType::GHOST) {
		modDmg += 1;
	}

	//dragon
	if (monsterType == MonsterType::DRAGON && turn % 3 == 0) {
		modDmg += 3;
	}
	return modDmg;
}

void Monster::takeModeDamage(int incomingDmg, Obj_game& attacker) {
	int finalDmg = incomingDmg;
	DamageType attacktype = attacker.getweapon().damage_type;

	//skeleten
	if (monsterType == MonsterType::SKELETEN && attacktype == DamageType::BLUDGEONING) {
		finalDmg *= 2;
	}

	//slime
	if (monsterType == MonsterType::SLIME && attacktype == DamageType::SLASHING) {
		finalDmg = strength;
	}

	//golem
	if (monsterType == MonsterType::GOLEM) {
		finalDmg -= endurance;
	}

	takeDamage(finalDmg);
}