#pragma once

#include "Level.h"
#include "Room/IRoom.h"
#include "Room/Room.h"
#include "Room/BossRoom.h"
#include "Room/StartRoom.h"
#include "Room/StairsRoom.h"
#include "Room/Nothing.h"

namespace RogueLike { namespace Model {

	Level::Level(int width, int height, int depth, int maxdepth) 
	{
		this->width = width;
		this->height = height;
		this->level = depth;
		this->maxDepth = maxdepth;

		GenerateMap();
	}

	char* Level::GetMap(const int w, const int h)
	{
		return nullptr;
	}

	void Level::GenerateMap()
	{
		int maxLength = width + height;
		int randomDungeonLength = Random<int>::GetRandom((maxLength * 0.8), maxLength);
		
		int startLoc[] = { Random<int>::GetRandom(0, width - 1) , Random<int>::GetRandom(0, height - 1) };

		IRoom* r;
		// 100% loop
		for (int i = 0; i < randomDungeonLength; i++)
		{
			if (i == 0 && level == 0) {
				r = new StartRoom();
			}
			else if (i == 0) {
				r = new StairsRoom();
				r->isDirectionDown = false;
			}
			else if (i == randomDungeonLength && level == maxDepth) {
				r = new BossRoom();
			}
			else if (i == randomDungeonLength) {
				r = new StairsRoom();
				r->isDirectionDown = true;
			}
			else {
				r = new Room;
			}
			locations.insert(locations.end, r);
		}

		// 50% loop
		for (int i = 0; i < locations.size; i++)
		{
			if ((Random<int>::GetRandom(0, 1)) == 0) {

			}
		}

		// 20% loop
		for (int i = 0; i < height; i++)
		{
			if ((Random<int>::GetRandom(0, 4)) == 0) {

			}
		}

		locations = std::vector<IRoom*>(width * height);

		for (int i=0; i < locations.size(); i++)
		{
			locations[i] = new Room();
		}

		int x = 5, y = 5;
		IRoom* answer = locations[y * width + x];

		/*for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				std::cout << ". ";
			}
			std::cout << std::endl << std::endl;
		}*/
	}

} }