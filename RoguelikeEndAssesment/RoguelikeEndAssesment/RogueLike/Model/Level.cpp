#include "Level.h"

#include <iomanip>

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
	Level::~Level()
	{
		std::cout << "Destructor: Level" << std::endl;
		if (!_locations.empty())
		{
			for (unsigned int i = 0; i < _locations.size(); i++)
				delete _locations[i];
			_locations.clear();
		}
		_startPoint = nullptr;
		_endPoint = nullptr;
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
		//int maxLength = _width + _height;
		int maxLength = (_width * _height) - ((_width * _height) / 2);
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
		//std::cout << "Random Length: " << randomDungeonLength << std::endl;
	}

	void Level::createLevelPath(Room::IRoom* previousRoom, Room::IRoom* currentRoom, int dungeonLength) 
	{
		if (dungeonLength < 1) {
			Room::IRoom* end = new Room::StairsRoom('E', currentRoom->GetX(), currentRoom->GetY(), true);
			this->_endPoint = end;
			if(currentRoom)
				delete currentRoom;
			_locations[end->GetY() * _width + end->GetX()] = end;
			return;
		}
		
		//std::cout << "Pos: " << std::setw(2) << currentRoom->GetX() << ", " << std::setw(2) << currentRoom->GetY();

		// Check available rooms
		bool availableDirections[] = {true, true, true, true};
		bool walls[] = {
			(currentRoom->GetY() <= 0),
			(currentRoom->GetX() != 0 && (currentRoom->GetX() % (_width - 1)) == 0),
			(currentRoom->GetY() >= _height-1),
			((currentRoom->GetX() % _width) == 0)
		};
		int maxDirections = 4;
		
		//std::cout << " ---:";
		int previousRoomX = (previousRoom != nullptr) ? previousRoom->GetX() : -2;
		int previousRoomY = (previousRoom != nullptr) ? previousRoom->GetY() : -2;

		//std::string dirCheck = "";

		// North
		if (previousRoomY == (currentRoom->GetY() - 1) ||
			!(!walls[0] && !(_locations[(currentRoom->GetY() - 1) * _width + currentRoom->GetX()]->GetRealIcon() != '.')))
		{
			maxDirections--;
			availableDirections[0] = false;
			//dirCheck += " North ";
		}
		// East
		if (previousRoomX == (currentRoom->GetX() + 1) ||
			!(!walls[1] && !(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() + 1)]->GetRealIcon() != '.')))
		{
			maxDirections--;
			availableDirections[1] = false;
			//dirCheck += " East ";
		}
		// South
		if (previousRoomY == (currentRoom->GetY() + 1) ||
			!(!walls[2] && !(_locations[(currentRoom->GetY() + 1) * _width + currentRoom->GetX()]->GetRealIcon() != '.')))
		{
			maxDirections--;
			availableDirections[2] = false;
			//dirCheck += " South ";
		}
		// West
		if (previousRoomX == (currentRoom->GetX() - 1) ||
			!(!walls[3] && !(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() - 1)]->GetRealIcon() != '.')))
		{
			maxDirections--;
			availableDirections[3] = false;
			//dirCheck += " West ";
		}

		bool isStuck = (maxDirections == 0) ? true : false;

		if (isStuck) // Make it possible to choose out of 4 directions if you are stuck.
			maxDirections = 4;
	
		// Get random int from no of available rooms
		int roomDirection = Random::GetRandom(0, 4);

		int clockwise = Random::GetRandom(0,1);
		//std::cout << std::setw(26) << dirCheck;
		//std::cout << ", rDir(" << roomDirection << "), " << " isStuck: " << isStuck << ", clock: " << clockwise;

		// Set current room in right direction
		int direction = roomDirection;

		if (clockwise == 0)
		{
			for (int i = roomDirection; i < (roomDirection + 4); i++)
			{
				int j = (i >= 4) ? (i - 4) : i;
				if ((j == direction && (availableDirections[j] == false || isStuck == true) && isStuck == false) || (j == direction && walls[j] == true))
				{
					if (direction >= 3)
						direction = 0;
					else
						direction += 1;
				}
			}
		} 
		else
		{
			for (int i = roomDirection; i >= (roomDirection - 4); i--)
			{
				int j = (i < 0) ? (i + 4) : i;
				if ((j == direction && (availableDirections[j] == false || isStuck == true) && isStuck == false) || (j == direction && walls[j] == true))
				{
					if (direction < 0)
						direction = 3;
					else
						direction -= 1;
				}
			}
		}
		//std::cout << ", chosenDir: " << direction;

		Room::IRoom* newRoom;
		int x = currentRoom->GetX() + ((direction == 1 || direction == 3) ? ((direction == 1) ? 1 : -1) : 0);
		int y = currentRoom->GetY() + ((direction == 0 || direction == 2) ? ((direction == 2) ? 1 : -1) : 0);
		//std::cout << ", direction headed: (" << x << ", " << y << "); curLength: " << dungeonLength << std::endl;

		if (isStuck) {
			newRoom = _locations[(y * _width) + x];
		} else {
			newRoom = new Room::Room('N', x, y);
			if(_locations[y * _width + x])
				delete _locations[y * _width + x]; // delete room.
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