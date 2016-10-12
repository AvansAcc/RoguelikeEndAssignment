#pragma once
#include <random>
#include <ctime>

template <class T>
class Random
{
private:

public:
	static T GetRandom(const int min, const int max)
	{
		std::default_random_engine generator;
		generator.seed(time(0));
		std::uniform_int_distribution<T> distribution1(min, max);
		return distribution1(generator);
	}
};