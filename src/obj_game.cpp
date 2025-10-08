#include "obj_game.h"

void Obj_game::takeDamage(int damage) {
	if (damage > 0) {
		hp -= damage;
	}
}

bool Obj_game::isAlive() const {
	return hp > 0;
}