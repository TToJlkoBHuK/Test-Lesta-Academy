#pragma once
#include <string>

class DamageType {
public:
	virtual ~DamageType() = default;
	virtual std::string getName() const = 0;
};

class Piercing : public DamageType {
public:
	std::string getName() const override;
};

class Slashing : public DamageType {
public:
	std::string getName() const override;
};

class Bludgeoning : public DamageType {
public:
	std::string getName() const override;
};