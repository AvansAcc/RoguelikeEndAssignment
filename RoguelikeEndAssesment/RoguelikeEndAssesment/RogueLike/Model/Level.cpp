#pragma once

#include "Level.h"
#include "Room/IRoom.h"
#include "Room/Room.h"
#include "Room/BossRoom.h"
#include "Room/StartRoom.h"
#include "Room/StairsRoom.h"
#include "Room/Nothing.h"

namespace RogueLike { namespace Model {

	Level::Level(int width, int height, int depth) 
	{
		this->width = width;
		this->height = height;
		this->depth = depth;


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

		//IRoom* r;
		//// 100% loop
		//for (int i = 0; i < randomDungeonLength; i++)
		//{
		//	if (i == 0 && depth == 0) {
		//		r = new StartRoom();
		//	}
		//	else if (i == 0) {
		//		r = new StairsRoom();
		//		r.direction = up;
		//	}
		//	else if (i == randomDungeonLength && depth == maxdepth) {
		//		r = new BossRoom();
		//	}
		//	else if (i == randomDungeonLength) {
		//		r = new StairsRoom();
		//		r.direction = down;
		//	}
		//	*locations
		//}

		//// 50% loop
		//for (int i = 0; i < height; i++)
		//{

		//}

		//// 20% loop
		//for (int i = 0; i < height; i++)
		//{

		//}

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