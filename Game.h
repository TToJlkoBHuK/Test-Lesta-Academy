#pragma once
#include "Player.h"
#include "Monster.h"
#include <memory>
#include <optional>

class Game {
public:
	void run();

private:
	void showStartMenu();
	void createCharacter();
	void mainloop();
	std::optional<Weapon> battle();
	void postbattlevict(const Weapon& droppedWeapon);
	void lvlupscreen();
	void weaponChoiseScreen(const Weapon& dropweapon);

	std::unique_ptr<Player> player;
	int wins = 0;
};