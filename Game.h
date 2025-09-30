#pragma once
#include "Player.h"
#include "Monster.h"
#include <memory>

class Game {
public:
	void run();

private:
	void showStartMenu();
	void createCharacter();
	void mainloop();
	bool battle();
	void postbattlevict();
	void lvlupscreen();
	void weaponChoiseScreen(const Weapon& dropweapon);

	std::unique_ptr<Player> player;
	int wins = 0;
};