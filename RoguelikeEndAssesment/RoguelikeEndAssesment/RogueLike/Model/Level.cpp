#pragma once

#include "Level.h"

namespace RogueLike { namespace Model {
	int width;
	int height;
	int depth;
	IRoom* locations;

	Level::Level(int width, int height, int depth) 
	{

	}

	char* Level::GetMap(const int w, const int h)
	{

	}

	void Level::GenerateMap()
	{
		int maxLength = width + height;
		int randomDungeonLength = Random<int>::GetRandom((maxLength * 0.8), maxLength);

	}

} }