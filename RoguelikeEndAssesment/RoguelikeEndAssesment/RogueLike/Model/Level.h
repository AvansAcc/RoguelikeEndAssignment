#pragma once

#include <iostream>
#include <typeinfo>
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
		Room::IRoom* _startPoint;
		Room::IRoom* _endPoint;
	public:

	private:
		void createLevelPath(Room::IRoom* previousRoom, Room::IRoom* currentRoom, int dungeonLength, std::vector<Room::Room*> *tempList);
		void createExtraPath(const int percentage, int roomIndex, std::vector<Room::Room*> *tempList);
	public:
		Level(int width, int height, int level, int maxDepth);
		virtual ~Level();
		const char* const GetMap(); // For your viewing purposes
		void GenerateMap();
		const int GetLevel() const { return this->_level; }

		const unsigned int GetWidth() const { return this->_width; }
		const unsigned int GetHeight() const { return this->_height; }
	};
} }