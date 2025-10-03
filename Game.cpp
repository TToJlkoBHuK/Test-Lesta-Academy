#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <optional>

void Game::run() {
	while (true) {
		showStartMenu();
		createCharacter();
		mainloop();
	}
}

void Game::showStartMenu() {
	std::cout << "=== NEW AUTOBATTLER ===" << std::endl;
	std::cout << "1. Start new game " << std::endl;
	std::cout << "2. Exit" << std::endl;

	int choice;
	std::cin >> choice;
	if (choice == 2) {
		exit(0);
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::createCharacter() {
	std::cout << "\nChoice class:" << std::endl;
	std::cout << "1. Rogue" << std::endl;
	std::cout << "2. Warriour" << std::endl;
	std::cout << "3. Barbarian" << std::endl;

	int choice;
	std::cin >> choice;

	CharacterClass selectedClass;
	switch (choice) {
		case 1: selectedClass = CharacterClass::ROGUE; break;
		case 2: selectedClass = CharacterClass::WARRIOR; break;
		case 3: selectedClass = CharacterClass::BARBARIAN; break;
		default: selectedClass = CharacterClass::WARRIOR; break;
	}
	player = std::make_unique<Player>(selectedClass);
	wins = 0;

	std::cout << "\n--- You created new hero! ---" << std::endl;
	std::cout << "Strength: " << player->getstrength() << ", Dexteity: " << player->getdexterity()
		<< ", Endurance: " << player->getendurance() << std::endl;
	std::cout << "HP " << player->gethp() << "/" << player->getmaxhp() << std::endl;
	std::cout << "Weapon: " << player->getweapon().name << " (damage: " << player->getweapon().damage << ")" << std::endl;
}

void Game::mainloop() {
	while (wins < 5) {
		auto victory = battle();
		if (victory) {
			wins++;
			std::cout << "\n*** Win! Monsters licvidated: " << wins << " from 5 ***" << std::endl;
			if (wins == 5) {
				std::cout << "\nYou end game!\n" << std::endl;
				return;
			}
			postbattlevict(victory.value());
		}
		else {
			std::cout << "\n--- You loser. Try again. ---\n" << std::endl;
			return;
		}
	}
}

std::optional<Weapon> Game::battle() {
    Monster monster(static_cast<MonsterType>(getRandom(0, 5)));
    std::cout << "\n--- Start fight! Your enemy: " << monster.getName() << " ---" << std::endl;

    Obj_game* attacker;
    Obj_game* defender;
    if (player->getdexterity() >= monster.getdexterity()) {
        attacker = player.get();
        defender = &monster;
    }
    else {
        attacker = &monster;
        defender = player.get();
    }

    int turn = 1;
    while (player->isAlive() && monster.isAlive()) {
        std::cout << "\n--- motion " << turn << " ---" << std::endl;
        std::cout << "hp player: " << player->gethp() << " | hp monster: " << monster.gethp() << std::endl;

        std::cout << attacker->getName() << " attack " << defender->getName() << "!" << std::endl;
        int hitChanceRoll = getRandom(1, attacker->getdexterity() + defender->getdexterity());
        if (hitChanceRoll > defender->getdexterity()) {
            if (dynamic_cast<Player*>(attacker)) {
                int baseDmg = dynamic_cast<Player*>(attacker)->calcBaseDamage(*defender);
                int modifiedDmg = dynamic_cast<Player*>(attacker)->applyDamageMode(baseDmg, *defender, turn);
                dynamic_cast<Monster*>(defender)->takeModeDamage(modifiedDmg, *attacker);
                std::cout << attacker->getName() << " applies " << modifiedDmg << " damage." << std::endl;
            }
            else {
                int baseDmg = dynamic_cast<Monster*>(attacker)->calcBaseDamage();
                int modifiedDmg = dynamic_cast<Monster*>(attacker)->applyDamageMode(baseDmg, turn);
                dynamic_cast<Player*>(defender)->takeModeDamage(modifiedDmg, *attacker, turn);
                std::cout << attacker->getName() << " applies " << modifiedDmg << " damage." << std::endl;
            }
        }
        else {
            std::cout << attacker->getName() << " missed!" << std::endl;
        }

        if (!defender->isAlive()) break;

        std::swap(attacker, defender);
        std::cout << attacker->getName() << " attack " << defender->getName() << "!" << std::endl;
        hitChanceRoll = getRandom(1, attacker->getdexterity() + defender->getdexterity());
        if (hitChanceRoll > defender->getdexterity()) {
            if (dynamic_cast<Player*>(attacker)) {
                int baseDmg = dynamic_cast<Player*>(attacker)->calcBaseDamage(*defender);
                int modifiedDmg = dynamic_cast<Player*>(attacker)->applyDamageMode(baseDmg, *defender, turn);
                dynamic_cast<Monster*>(defender)->takeModeDamage(modifiedDmg, *attacker);
                std::cout << attacker->getName() << " applies " << modifiedDmg << " damage." << std::endl;
            }
            else {
                int baseDmg = dynamic_cast<Monster*>(attacker)->calcBaseDamage();
                int modifiedDmg = dynamic_cast<Monster*>(attacker)->applyDamageMode(baseDmg, turn);
                dynamic_cast<Player*>(defender)->takeModeDamage(modifiedDmg, *attacker, turn);
                std::cout << attacker->getName() << " applies " << modifiedDmg << " damage." << std::endl;
            }
        }
        else {
            std::cout << attacker->getName() << " missed!" << std::endl;
        }

        turn++;
    }

    if (player->isAlive()) {
        return monster.getloot();
    }
    else {
        return std::nullopt;
    }
}

void Game::postbattlevict(const Weapon& droppedweapon) {
    player->fullheal();
    std::cout << "You have max hp!" << std::endl;

    weaponChoiseScreen(droppedweapon);

    if (player->getTotallvl() < 3) {
        lvlupscreen();
    }

    std::cout << "\n--- specifications now ---" << std::endl;
    std::cout << "strenght: " << player->getstrength() << ", dexterity: " << player->getdexterity()
        << ", endurance: " << player->getendurance() << std::endl;
    std::cout << "HP: " << player->gethp() << "/" << player->getmaxhp() << std::endl;
    std::cout << "Weapon: " << player->getweapon().name << " (damage: " << player->getweapon().damage << ")" << std::endl;
}

void Game::lvlupscreen() {
    std::cout << "\nCoice class from up lvl:" << std::endl;
    std::cout << "1. Rogue" << std::endl;
    std::cout << "2. Warriour" << std::endl;
    std::cout << "3. Barbarian" << std::endl;
    int choice;
    std::cin >> choice;

    CharacterClass selectedClass;
    switch (choice) {
    case 1: selectedClass = CharacterClass::ROGUE; break;
    case 2: selectedClass = CharacterClass::WARRIOR; break;
    case 3: selectedClass = CharacterClass::BARBARIAN; break;
    default: return;
    }
    player->lvlup(selectedClass);
}

void Game::weaponChoiseScreen(const Weapon& droppedWeapon) {
    std::cout << "\nMonster dropped weapon: " << droppedWeapon.name << " (damage: " << droppedWeapon.damage << ")" << std::endl;
    std::cout << "Your weapon now: " << player->getweapon().name << " (damge: " << player->getweapon().damage << ")" << std::endl;
    std::cout << "Do you want to replace? (1 - y, 2 - n): ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        player->equipWeapon(droppedWeapon);
        std::cout << "You epicured" << droppedWeapon.name << "!" << std::endl;
    }
}