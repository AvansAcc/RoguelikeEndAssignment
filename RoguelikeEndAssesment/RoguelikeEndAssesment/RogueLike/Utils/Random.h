#pragma once

#include <random>
#include <ctime>

class Random
{
public:
	static bool Random::seeded;
public:
	static void SeedRandom(unsigned int number);
	static int GetRandom(const int min, const int max);
};