#pragma once
#include "obj_game.h"
#include "TypeRegistry.h"



class Monster : public Obj_game {
public:
	virtual ~Monster() = default;
	Weapon getloot() const { return loot; }

	//fight logical
	virtual int calcBaseDamage() { return currentWeapon.damage + strength; }
	virtual int applyDamageMode(int baseDamage, int turn) { return baseDamage; }
	virtual void takeModeDamage(int incomingDamage, Obj_game& attack);

protected:
	Weapon loot;
};

class MonsterFactory {
public:
	static std::unique_ptr<Monster> createRandomMonster();
};

class Goblin : public Monster {
public:
	Goblin();
};

class Skeleton : public Monster {
public:
	Skeleton();
	void takeModeDamage(int incomingDamage, Obj_game& attaker) override;
};

class Slime : public Monster {
public:
	Slime();
	void takeModeDamage(int incomingDamage, Obj_game& attaker) override;
};

class Ghost : public Monster {
public:
	Ghost();
	int applyDamageMode(int baseDamage, int turn) override;
};

class Golem : public Monster {
public:
	Golem();
	void takeModeDamage(int incomingDamage, Obj_game& attaker) override;
};

class Dragon : public Monster {
public:
	Dragon();
	int applyDamageMode(int baseDamage, int turn) override;
};