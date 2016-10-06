#pragma once

#include "Room\IRoom.h"

namespace RogueLike { namespace Model {
	class Level {
	private:
		int width;
		int height;
		IRoom* locations;
	public:
		Level(int width, int height);
		char* GetMap(const int w, const int h);
	};
} }