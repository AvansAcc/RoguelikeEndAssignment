#include <random>
#include <ctime>

template <class T>
class Random
{
private:
	std::default_random_engine generator;
public
	template <class T>
	T GetRandom<T>(int min, int max)
	{
		generator.seed(time(0));
		std::uniform_int_distribution<T> distribution1(min, max);
		return distribution1(generator);
	}
};