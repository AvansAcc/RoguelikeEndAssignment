#pragma once

#include <iostream>
#include <typeinfo>
#include "../Utils/Random.h"
#include "../Common.h"

#include "Room/IRoom.h"
#include "Room/Room.h"
#include "Room/BossRoom.h"
#include "Room/StartRoom.h"
#include "Room/StairsRoom.h"
#include "Room/Nothing.h"
#include "../Utils/File.h"
#include "../ErrorHandling/FileNotFoundException.h"

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
		Level(const Level& other);
		Level(Level&& other);
		Level& operator=(const Level& other);
		Level& operator=(Level&& other);

		const char* const GetMap(const int player_x, const int player_y); // For your viewing purposes
		void GenerateMap();

		const std::vector<Room::IRoom*> GetLocations() const { return this->_locations; }
		const Room::IRoom* GetStartPoint() const { return this->_startPoint; };
		const Room::IRoom* GetEndPoint() const { return this->_endPoint; };
		const unsigned int GetWidth() const { return this->_width; }
		const unsigned int GetHeight() const { return this->_height; }
		const unsigned int GetMaxDepth() const { return this->_maxDepth; }

		const std::string GetLevelAsString() const;
	};
} }