#pragma once
#include "DamageType.h"
#include "WeaponType.h"

class TypeRegisrtry {
public:
	static const DamageType& getPiercing();
	static const DamageType& getSlashing();
	static const DamageType& getBludgeoning();

	static const WeaponType& getDagger();
	static const WeaponType& getSword();
	static const WeaponType& getClub();
	static const WeaponType& getAxe();
	static const WeaponType& getSpear();
	static const WeaponType& getLegendarySword();
};
