#include "Level.h"

namespace RogueLike { namespace Model {

	Level::Level(int width, int height, int depth, int maxdepth) 
	{
		this->_width = width;
		this->_height = height;
		this->_level = depth;
		this->_maxDepth = maxdepth;
		this->_locations.clear();

		Room::Nothing* n;
		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				n = new Room::Nothing('.', x, y);
				_locations.push_back(n);
			}
		}
		this->_startPoint = nullptr;
		this->_endPoint = nullptr;
	}

	char* Level::GetMap(const int w, const int h)
	{
		if (_locations.empty() || w <= 0 || h <= 0)
			return nullptr;

		char* map = new char[w * h];
		for (int i=0; i < w * h; i++)
		{
			map[i] = this->_locations[i]->GetIcon();
		}
		return map;
	}

	void Level::GenerateMap()
	{
		int maxLength = _width + _height;
		int randomDungeonLength = Random::GetRandom((int)(maxLength * 0.8), maxLength);
		int startLoc[] = { Random::GetRandom(0, _width - 1), Random::GetRandom(0, _height - 1) };

		//Room::IRoom* r = nullptr;

		// 100% loop
		/*for (int i = 0; i < randomDungeonLength; i++)
		{
			int x = _locations[(startLoc[1] * _width) + startLoc[0]]->GetX();
			int y = _locations[(startLoc[1] * _width) + startLoc[0]]->GetY();

			if (i == 0 && _level == 0) {
				r = new Room::StartRoom('S', x, y);
				_locations[(startLoc[1] * _width) + startLoc[0]] = r;
			}
			else if (i == 0) {
				r = new Room::StairsRoom('^', x, y, false);
				_locations[(startLoc[1] * _width) + startLoc[0]] = r;
			}
			else if (i == randomDungeonLength && _level == _maxDepth) {
				r = new Room::BossRoom('B', x, y);
			}
			else if (i == randomDungeonLength) {
				r = new Room::StairsRoom('v', x, y, true);
				//((Room::StairsRoom*)r)->IsDirectionDown = true;
			}
			else {
				r = new Room::Room('R', 0, 0);
				//_locations[i - 1]->AddAdjacentRoom(r);
			}
		}

		// 50% loop
		for (unsigned int i = 0; i < _locations.size(); i++)
		{
			if ((Random<int>::GetRandom(0, 1)) == 0) {
				//((Room::Room*)_locations[i])->

			}
		}

		// 20% loop
		for (int i = 0; i < this->_height; i++)
		{
			if ((Random<int>::GetRandom(0, 5)) == 0) {
				// TODO: Create Level 20% loop
			}
		}*/

		int x = _locations[(startLoc[1] * _width) + startLoc[0]]->GetX();
		int y = _locations[(startLoc[1] * _width) + startLoc[0]]->GetY();
		_startPoint = new Room::StartRoom('S', x, y);
		_locations[(startLoc[1] * _width) + startLoc[0]] = _startPoint;
		
		this->createLevelPath(nullptr, _startPoint, randomDungeonLength);
		std::cout << "Random Length: " << randomDungeonLength << std::endl;
	}

	void Level::createLevelPath(Room::IRoom* previousRoom, Room::IRoom* currentRoom, int dungeonLength) 
	{
		if (dungeonLength < 1) {
			Room::IRoom* end = new Room::StairsRoom('E', currentRoom->GetX(), currentRoom->GetY(), true);
			this->_endPoint = end;
			delete currentRoom;
			_locations[end->GetY() * _width + end->GetX()] = end;
			return;
		}
		
		std::cout << "Pos: " << currentRoom->GetX() << ", " << currentRoom->GetY();

		// Check available rooms
		bool availableDirections[] = {true, true, true, true};
		bool walls[] = {
			(currentRoom->GetY() <= 0),
			((currentRoom->GetX() % (_width - 1)) == 0),
			(currentRoom->GetY() >= _height),
			((currentRoom->GetX() % _width) == 0)
		};
		int maxDirections = 4;
		
		std::cout << " Not safe: ";
		int previousRoomX = (previousRoom != nullptr) ? previousRoom->GetX() : -2;
		int previousRoomY = (previousRoom != nullptr) ? previousRoom->GetY() : -2;


		// North
		if (previousRoomY == (currentRoom->GetY() - 1) ||
			!(!walls[0] && !(_locations[(currentRoom->GetY() - 1) * _width + currentRoom->GetX()]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[0] = false;
			std::cout << " North ";
		}
		// East
		if (previousRoomX == (currentRoom->GetX() + 1) ||
			!(!walls[1] && !(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() + 1)]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[1] = false;
			std::cout << " East ";
		}
		// South
		if (previousRoomY == (currentRoom->GetY() + 1) ||
			!(!walls[2] && !(_locations[(currentRoom->GetY() + 1) * _width + currentRoom->GetX()]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[2] = false;
			std::cout << " South ";
		}
		// West
		if (previousRoomX == (currentRoom->GetX() - 1) ||
			!(!walls[3] && !(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() - 1)]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[3] = false;
			std::cout << " West ";
		}

		bool isStuck = (maxDirections == 0) ? true : false;

		if (isStuck)
			maxDirections = 4;
	
		// Get random int from no of available rooms
		int roomDirection = Random::GetRandom(0, maxDirections);

		std::cout << " : max(" << maxDirections << ") , dir(" << roomDirection << "), " << " isStuck: " << isStuck;

		// Set current room in right direction
		int direction = roomDirection;
		for (int i = 0; i < maxDirections; i++)
		{
			if (i == direction && !isStuck && availableDirections[i] == true)
			{
				if (direction >= 4)
					direction = 0;
				else
					direction++;
			}
		}

		Room::IRoom* newRoom;
		int x = currentRoom->GetX() + ((direction == 1 || direction == 3) ? ((direction == 1) ? 1 : -1) : 0);
		int y = currentRoom->GetY() + ((direction == 0 || direction == 2) ? ((direction == 2) ? 1 : -1) : 0);
		std::cout << ", direction headed: (" << x << ", " << y << "); curLength: " << dungeonLength << std::endl;

		if (isStuck) {
			newRoom = _locations[(y * _width) + x];
		} else {
			newRoom = new Room::Room('N', x, y);
			delete _locations[y * _width + x]; // delete nothing.
			_locations[y * _width + x] = newRoom;
			dungeonLength--;
		}
		
		// Link current room with last room and back
		((Room::Room*)currentRoom)->AddAdjacentRoom(newRoom, direction);
		((Room::Room*)newRoom)->AddAdjacentRoom(currentRoom, (direction > 1) ? direction - 2 : direction + 2);

		createLevelPath(currentRoom, newRoom, dungeonLength);
	}

	/*void Level::createExtraPath(int percentage, Room::IRoom* currentRoom)
	{
		std::cout << std::endl << std::endl << "ExtraPath: " << std::endl;
		std::cout << "Pos: " << currentRoom->GetX() << ", " << currentRoom->GetY();

		// Check available rooms
		bool availableDirections[] = { true, true, true, true };
		bool walls[] = {
			(currentRoom->GetY() <= 0),
			((currentRoom->GetX() % (_width - 1)) == 0),
			(currentRoom->GetY() >= _height),
			((currentRoom->GetX() % _width) == 0)
		};
		int maxDirections = 4;

		// North
		if (previousRoomY == (currentRoom->GetY() - 1) ||
			!(!walls[0] && !(_locations[(currentRoom->GetY() - 1) * _width + currentRoom->GetX()]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[0] = false;
			std::cout << " North ";
		}
		// East
		if (previousRoomX == (currentRoom->GetX() + 1) ||
			!(!walls[1] && !(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() + 1)]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[1] = false;
			std::cout << " East ";
		}
		// South
		if (previousRoomY == (currentRoom->GetY() + 1) ||
			!(!walls[2] && !(_locations[(currentRoom->GetY() + 1) * _width + currentRoom->GetX()]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[2] = false;
			std::cout << " South ";
		}
		// West
		if (previousRoomX == (currentRoom->GetX() - 1) ||
			!(!walls[3] && !(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() - 1)]->GetIcon() != '.')))
		{
			maxDirections--;
			availableDirections[3] = false;
			std::cout << " West ";
		}

		Random::GetRandom(0, maxDirections);
	}*/

} }