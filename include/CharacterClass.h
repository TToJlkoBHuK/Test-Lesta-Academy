#pragma once
#include <string>
#include <memory>
#include "Weapon.h"

class Player;
class Obj_game;

class CharacterClass {
public:
	virtual ~CharacterClass() = default;
	
	virtual std::string getName() const = 0;
	virtual int getBaseHPLvl() const = 0;
	virtual Weapon getStartWeapon() const = 0;

	virtual int applyDmgBonus(int currentDmg, int lvl, Player& player, Obj_game& target, int turn) const = 0;
	virtual int applyDefBonus(int incomingDmg, int lvl, Player& player, Obj_game& attacker, int turn) const = 0;
	virtual void applyStatBonus(int lvl, int& str, int& dex, int& end) const = 0;
};

class Rouge : public CharacterClass {
public:
	std::string getName() const override { return "Rouge"; }
	int getBaseHPLvl() const override { return 4; }
	Weapon getStartWeapon() const override;
	int applyDmgBonus(int currentDmg, int lvl, Player& player, Obj_game& target, int turn) const override;
	int applyDefBonus(int incomingDmg, int lvl, Player& player, Obj_game& attacker, int turn) const override;
	void applyStatBonus(int lvl, int& str, int& dex, int& end) const override;
};

class Warrior : public CharacterClass {
public:
	std::string getName() const override { return "Warrior"; }
	int getBaseHPLvl() const override { return 5; }
	Weapon getStartWeapon() const override;
	int applyDmgBonus(int currentDmg, int lvl, Player& player, Obj_game& target, int turn) const override;
	int applyDefBonus(int incomingDmg, int lvl, Player& player, Obj_game& attacker, int turn) const override;
	void applyStatBonus(int lvl, int& str, int& dex, int& end) const override;
};

class Barbarian : public CharacterClass {
public:
	std::string getName() const override { return "Barbarian"; }
	int getBaseHPLvl() const override { return 6; }
	Weapon getStartWeapon() const override;
	int applyDmgBonus(int currentDmg, int lvl, Player& player, Obj_game& target, int turn) const override;
	int applyDefBonus(int incomingDmg, int lvl, Player& player, Obj_game& attacker, int turn) const override;
	void applyStatBonus(int lvl, int& str, int& dex, int& end) const override;
};

class CharacterClassFactory {
public:
	static std::unique_ptr<CharacterClass> create(const std::string& className);
};