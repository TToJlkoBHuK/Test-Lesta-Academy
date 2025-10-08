#pragma once
#include <string>
#include "TypeRegistry.h"

struct Weapon {
	std::string name;
	int damage = 0;
	const DamageType* damage_type = nullptr;
	const WeaponType* weapon_type = nullptr;
};