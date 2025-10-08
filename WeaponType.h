#pragma once
#include <string>

class WeaponType {
public:
	virtual ~WeaponType() = default;
	virtual std::string getName() const = 0;
};

class Dagger : public WeaponType {
public:
	std::string getName() const override;
};

class Sword : public WeaponType {
public:
	std::string getName() const override;
};

class Club : public WeaponType {
public:
	std::string getName() const override;
};

class Axe : public WeaponType {
public:
	std::string getName() const override;
};

class Spear : public WeaponType {
public:
	std::string getName() const override;
};

class LegendarySword : public WeaponType {
public:
	std::string getName() const override;
};