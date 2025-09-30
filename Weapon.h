#pragma once
#include <string>
#include "Enum.h"

struct Weapon {
	std::string name;
	int damage = 0;
	DamageType damage_type;
	WeaponType weapon_type;
};