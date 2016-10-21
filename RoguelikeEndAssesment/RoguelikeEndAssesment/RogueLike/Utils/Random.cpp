#include "Random.h"

bool Random::seeded = false;

void Random::SeedRandom(unsigned int number)
{
	std::srand(number);
	Random::seeded = true;
}

int Random::GetRandom(int min, int max)
{
	if (Random::seeded == false)
		Random::SeedRandom((unsigned)std::time(0));
	if (max <= 0)
		max = 1;

	return ((std::rand() % (max - min)) + min);
}