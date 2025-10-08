#include "TypeRegistry.h"

const DamageType& TypeRegisrtry::getPiercing() {
	static Piercing instance;
	return instance;
}

const DamageType& TypeRegisrtry::getSlashing() {
	static Slashing instance;
	return instance;
}

const DamageType& TypeRegisrtry::getBludgeoning() {
	static Bludgeoning instance;
	return instance;
}

const WeaponType& TypeRegisrtry::getDagger() {
	static Dagger instance;
	return instance;
}

const WeaponType& TypeRegisrtry::getSword() {
	static Sword instance;
	return instance;
}

const WeaponType& TypeRegisrtry::getClub() {
	static Club instance;
	return instance;
}

const WeaponType& TypeRegisrtry::getAxe() {
	static Axe instance;
	return instance;
}

const WeaponType& TypeRegisrtry::getSpear() {
	static Spear instance;
	return instance;
}

const WeaponType& TypeRegisrtry::getLegendarySword() {
	static LegendarySword instance;
	return instance;
}