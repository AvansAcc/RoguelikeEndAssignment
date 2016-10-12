#pragma once

#include "Level.h"

namespace RogueLike { namespace Model {
	Level::Level(int width, int height, int depth) 
	{

	}

	char* Level::GetMap(const int w, const int h)
	{
		return nullptr;
	}

	void Level::GenerateMap()
	{
		int maxLength = width + height;
		int randomDungeonLength = Random<int>::GetRandom((maxLength * 0.8), maxLength);

		locations = std::vector<IRoom*>(width * height);

		for (int i=0; i < locations.size(); i++)
		{
			locations[i] = new Room();
		}

		int x = 5, y = 5;
		IRoom* answer = locations[y * width + x];
	}

} }