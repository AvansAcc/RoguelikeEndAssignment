#pragma once

#include <iostream>
#include "..\Utils\Random.h"
#include "../Common.h"

#include "Room/IRoom.h"
#include "Room/Room.h"
#include "Room/BossRoom.h"
#include "Room/StartRoom.h"
#include "Room/StairsRoom.h"
#include "Room/Nothing.h"

namespace RogueLike { namespace Model {
	class Level {
	private:
		int _width;
		int _height;
		int _level;
		int _maxDepth;
		std::vector<Room::IRoom*> _locations;

	public:
		Level(int width, int height, int level, int maxDepth);
		char* GetMap(const int w, const int h); // For your viewing purposes
		void GenerateMap();
		const int GetLevel() const { return this->_level; }

		const unsigned int GetWidth() const { return this->_width; }
		const unsigned int GetHeight() const { return this->_height; }
	};
} }