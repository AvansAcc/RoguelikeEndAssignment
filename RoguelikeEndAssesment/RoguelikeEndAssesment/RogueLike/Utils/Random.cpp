#include "Random.h"

bool Random::seeded = false;

void Random::SeedRandom(unsigned int number)
{
	srand(number);
	Random::seeded = true;
}

int Random::GetRandom(int min, int max)
{
	//std::mt19937 eng{ std::chrono::high_resolution_clock::now().time_since_epoch().count() };
	//return std::uniform_int_distribution<>(min, max)(eng);

	//std::srand((unsigned)std::time(NULL));

	/*srand((unsigned int)time(0));
	std::default_random_engine generator;
	generator.seed((unsigned int)time(0));
	std::uniform_int_distribution<T> distribution1(min, max);
	return distribution1(generator);*/

	if (Random::seeded == false)
		Random::SeedRandom((unsigned)std::time(0));
	if (max <= 0)
		max = 1;

	return ((std::rand() % (max - min)) + min);
}