#pragma once
#include "Player.h"
#include "Monster.h"
#include <memory>
#include <optional>

class Game {
public:
	Game() = default;
	~Game() = default;

	Game(const Game&) = delete;
	Game& operator = (const Game&) = delete;
	Game(Game&&) noexcept = default;
	Game& operator = (Game&&) noexcept = default;

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