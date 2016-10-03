#pragma once

#include "Room\IRoom.h"

namespace RogueLike { namespace Model {
	class Level {
	private:
		int width;
		int height;
		IRoom* locations;
	public:
		Level();
		char* GetMap();
	};
} }