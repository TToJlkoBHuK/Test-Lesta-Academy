#pragma once
#include "Weapon.h"
#include <string>
#include <memory>

class Obj_game {
public:
	virtual ~Obj_game() = default;

	//methods for fight
	void takeDamage(int damage);
	bool isAlive() const;

	//getter
	const std::string& getName() const { return name; }
	int gethp() const { return hp; }
	int getmaxhp() const { return maxhp; }
	int getstrength() const { return strength; }
	int getdexterity() const { return dexterity; }
	int getendurance() const { return endurance; }
	const Weapon& getweapon() const { return currentWeapon; }

protected:
	std::string name;
	int hp = 0;
	int maxhp = 0;
	int strength = 0;
	int dexterity = 0;
	int endurance = 0;
	Weapon currentWeapon;
};