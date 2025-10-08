#pragma once
#include <random>

inline int getRandom(int min, int max) {
	static std::mt19937 engine(std::random_device{}());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}