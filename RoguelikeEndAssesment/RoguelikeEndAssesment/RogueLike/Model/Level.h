#pragma once

#include "Room\IRoom.h"
#include "..\Utils\Random.h"

namespace RogueLike { namespace Model {
	class Level {
	private:
		int width;
		int height;
		int depth;
		IRoom* locations;
	public:
		Level(int width, int height, int depth);
		char* GetMap(const int w, const int h); // For your viewing purposes
		void GenerateMap();
	};
} }