#pragma once

#include <iostream>

#include "Room\IRoom.h"
#include "Room/Room.h"
#include "..\Utils\Random.h"

namespace RogueLike { namespace Model {
	class Level {
	private:
		int width;
		int height;
		int level;
		int maxDepth;
		std::vector<IRoom*> locations;

	public:
		Level(int width, int height, int level, int maxDepth);
		char* GetMap(const int w, const int h); // For your viewing purposes
		void GenerateMap();
		int GetLevel();
	};
} }