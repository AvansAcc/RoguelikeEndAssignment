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

		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				_locations.push_back(new Room::Nothing('.', x, y));
			}
		}
		this->_startPoint = nullptr;
		this->_endPoint = nullptr;
	}
	Level::~Level()
	{
		if (!_locations.empty()) {
			for (unsigned int i = 0; i < _locations.size(); i++)
				delete _locations[i];
			_locations.clear();
		}
		_startPoint = nullptr;
		_endPoint = nullptr;
	}
	const char* const Level::GetMap(const int player_x, const int player_y)
	{
		if (_locations.empty())
			return nullptr;

		int w_dim = (_width * 4 - 3);
		int h_dim = (_height * 2 - 1);

		int dimension = w_dim * h_dim;
		char* map = new char[dimension];

		bool isEven = false;
		for (int i = 0; i < dimension; i++)
		{
			if (i % w_dim == 0) {
				isEven = !isEven;
			}

			int x = ((i % w_dim) / 4);
			int y = (int)(i / w_dim) / 2;
			
			if (isEven) // If Even
			{
				int index = (i - (i / w_dim));

				if (index % 4 == 0) {
					if (x == player_x && y == player_y)
						map[i] = 'P';
					else
						map[i] = this->_locations[y * _width + x]->GetIcon();
				}
				else if (i > 0 && (index - 1) % 4 == 0) {
					map[i] = ' ';
				}
				else if (i > 0 && (index - 2) % 4 == 0) {
					if (this->_locations[y * _width + x]->GetRealIcon() != '.')
					{
						if (((Room::Room*)this->_locations[y * _width + x])->GetAdjacentRooms()[1] != nullptr) {
							if (((Room::Room*)this->_locations[y * _width + x])->IsDiscovered() || (x < _width && ((Room::Room*)this->_locations[y * _width + (x + 1)])->IsDiscovered()))
							{
								if (((Room::Room*)this->_locations[y * _width + x])->GetDestroyedCorridors()[1] == true &&
									((Room::Room*)this->_locations[y * _width + (x + 1)])->GetDestroyedCorridors()[3] == true)
								{
									map[i] = '~';
								}
								else {
									map[i] = '-';
								}
							}
							else
								map[i] = ' ';
						}
						else {
							map[i] = ' ';
						}
					}
					else {
						map[i] = ' ';
					}
				}
				else if (i > 0 && (index - 3) % 4 == 0) {
					map[i] = ' ';
				}
			}
			else // If Uneven
			{
				int index = (i - ((i / w_dim) * w_dim));
				if (index % 4 == 0)
				{
					if (this->_locations[y * _width + x]->GetRealIcon() != '.')
					{
						if (((Room::Room*)this->_locations[y * _width + x])->GetAdjacentRooms()[2] != nullptr)
						{
							if (((Room::Room*)this->_locations[y * _width + x])->IsDiscovered() || (y < _height && ((Room::Room*)this->_locations[(y + 1) * _width + x])->IsDiscovered())) 
							{
								if (((Room::Room*)this->_locations[y * _width + x])->GetDestroyedCorridors()[2] == true && 
									((Room::Room*)this->_locations[(y + 1) * _width + x])->GetDestroyedCorridors()[0] == true)
								{
									map[i] = '{';
								}
								else {
									map[i] = '|';
								}
							}
							else
								map[i] = ' ';
						}
						else 
						{
							map[i] = ' ';
						}
					}
					else
					{
						map[i] = ' ';
					}
				}
				else 
				{
					map[i] = ' ';
				}
			}
		}

		return map;
	}

	const std::vector<std::string> const Level::GetMonsterHpMap(const int player_x, const int player_y)
	{
		if (_locations.empty()) {
			return{};
		}

		int w_dim = (_width * 4 - 3);
		int h_dim = (_height * 2 - 1);

		int dimension = w_dim * h_dim;
		//int* map = new int[dimension];
		std::vector<std::string> map(dimension);

		bool isEven = false;
		for (int i = 0; i < dimension; i++)
		{
			if (i % w_dim == 0) {
				isEven = !isEven;
			}

			int x = ((i % w_dim) / 4);
			int y = (int)(i / w_dim) / 2;

			if (isEven) // If Even
			{
				int index = (i - (i / w_dim));

				if (index % 4 == 0) {
					if (x == player_x && y == player_y)
						map[i] = "PP";
					else
						map[i] = this->_locations[y * _width + x]->GetMonsterIcon();
				}
				else if (i > 0 && (index - 1) % 4 == 0) {
					map[i] = " ";
				}
				else if (i > 0 && (index - 2) % 4 == 0) {
					if (this->_locations[y * _width + x]->GetRealIcon() != '.')
					{
						if (((Room::Room*)this->_locations[y * _width + x])->GetAdjacentRooms()[1] != nullptr) {
							if (((Room::Room*)this->_locations[y * _width + x])->IsDiscovered() || (x < _width && ((Room::Room*)this->_locations[y * _width + (x + 1)])->IsDiscovered()))
								map[i] = "=";
							else
								map[i] = " ";
						}
						else {
							map[i] = " ";
						}
					}
					else {
						map[i] = " ";
					}
				}
				else if (i > 0 && (index - 3) % 4 == 0) {
					map[i] = " ";
				}
			}
			else // If Uneven
			{
				int index = (i - ((i / w_dim) * w_dim));
				if (index % 4 == 0)
				{
					if (this->_locations[y * _width + x]->GetRealIcon() != '.')
					{
						if (((Room::Room*)this->_locations[y * _width + x])->GetAdjacentRooms()[2] != nullptr)
						{
							if (((Room::Room*)this->_locations[y * _width + x])->IsDiscovered() || (y < _height && ((Room::Room*)this->_locations[(y + 1) * _width + x])->IsDiscovered()))
								map[i] = "||";
							else
								map[i] = "  ";
						}
						else
						{
							map[i] = "  ";
						}
					}
					else
					{
						map[i] = "  ";
					}
				}
				else
				{
					map[i] = " ";
				}
			}
		}

		return map;
	}

	void Level::GenerateMap(std::vector<Enemy*> enemies)
	{
		this->_enemies = enemies;
		//int maxLength = _width + _height;
		int maxLength = (_width * _height) - ((_width * _height) / 2);
		int randomDungeonLength = Random::GetRandom((int)(maxLength * 0.8), maxLength);
		int startLoc[] = { Random::GetRandom(0, _width - 1), Random::GetRandom(0, _height - 1) };

		int x = _locations[(startLoc[1] * _width) + startLoc[0]]->GetX();
		int y = _locations[(startLoc[1] * _width) + startLoc[0]]->GetY();
		
		if (_level <= 0) {
			_startPoint = new Room::StartRoom('S', x, y);
		}
		else {
			_startPoint = new Room::StairsRoom('^', x, y, false);
		}
		
		if (_locations[(startLoc[1] * _width) + startLoc[0]])
			delete _locations[(startLoc[1] * _width) + startLoc[0]];
		((Room::Room*)_startPoint)->Discover();
		_locations[(startLoc[1] * _width) + startLoc[0]] = _startPoint;
		
		std::vector<Room::Room*> *_tempList = new std::vector<Room::Room*>();

		this->createLevelPath(nullptr, _startPoint, randomDungeonLength, _tempList);
		this->createExtraPath(2, 0, _tempList);

		/*if (Globals::PRERENDERFOES) {
			for each (Room::IRoom* iRoom in _locations) if (dynamic_cast<Room::Room*> (iRoom) != nullptr)
			{
				// Chance to spawn enemies in the room.
				if (dynamic_cast<Room::BossRoom*> (iRoom) != NULL)
					((Room::BossRoom*)iRoom)->ChanceSpawnRandomEnemies(enemies, this->_level, 0);
				else
					((Room::Room*)iRoom)->ChanceSpawnRandomEnemies(enemies, this->_level, 10);
			}
		}*/
		delete _tempList;
	}

	void Level::createLevelPath(Room::IRoom* previousRoom, Room::IRoom* currentRoom, int dungeonLength, std::vector<Room::Room*> *tempList)
	{
		if (dungeonLength < 1) {
			return;
		}
		

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

		int clockwise = Random::GetRandom(0, 2);
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
					if (direction <= 0)
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
			if (Globals::PRERENDERFOES) {
				((Room::Room*)newRoom)->ChanceSpawnRandomEnemies(this->_enemies, this->_level, 10);
			}
			if(_locations[y * _width + x])
				delete _locations[y * _width + x]; // delete room.
			_locations[y * _width + x] = newRoom;
			tempList->push_back((Room::Room*) newRoom);
			dungeonLength--;
		}
		
		if (dungeonLength < 1)
		{
			Room::IRoom* end; 
			if (_level == _maxDepth) {
				end = new Room::BossRoom('E', newRoom->GetX(), newRoom->GetY());
				if (Globals::PRERENDERFOES) {
					((Room::BossRoom*)end)->ChanceSpawnRandomEnemies(this->_enemies, this->_level, 0);
				}
			}
			else {
				end = new Room::StairsRoom('v', newRoom->GetX(), newRoom->GetY(), true);
			}
			this->_endPoint = end;
			if (newRoom)
				delete newRoom;
			_locations[end->GetY() * _width + end->GetX()] = end;

			tempList->pop_back();
			tempList->push_back((Room::Room*) end);

			newRoom = end;
		}

		// Link current room with last room and back
		((Room::Room*)currentRoom)->AddAdjacentRoom(newRoom, direction);
		((Room::Room*)newRoom)->AddAdjacentRoom(currentRoom, (direction > 1) ? direction - 2 : direction + 2);
		createLevelPath(currentRoom, newRoom, dungeonLength, tempList);
	}

	void Level::createExtraPath(const int percentage, int roomIndex, std::vector<Room::Room*> *tempList)
	{
		if (roomIndex >= (int)tempList->size()) {
			return;
		}
		
		//std::cout << std::endl;
		//std::cout << "Index: " << std::setw(3) << roomIndex << " size tempList: " << tempList->size();
		//std::cout << " ---:";

		int r = Random::GetRandom(0, percentage);
		if (r <= 0 )
		{
			Room::Room* currentRoom = nullptr;
			currentRoom = (*tempList)[roomIndex];

			//std::cout << " Pos: " << std::setw(2) << currentRoom->GetX() << ", " << std::setw(2) << currentRoom->GetY();

			// Check available rooms
			bool availableDirections[] = { true, true, true, true };
			bool walls[] = {
				(currentRoom->GetY() <= 0),
				(currentRoom->GetX() != 0 && (currentRoom->GetX() % (_width - 1)) == 0),
				(currentRoom->GetY() >= _height - 1),
				((currentRoom->GetX() % _width) == 0)
			};
			int maxDirections = 4;

			//std::string dirCheck = "";

			// North
			if (currentRoom->GetAdjacentRooms()[0] != nullptr || walls[0])
			{
				maxDirections--;
				availableDirections[0] = false;
				//dirCheck += " North ";
			}
			// East
			if (currentRoom->GetAdjacentRooms()[1] != nullptr || walls[1])
			{
				maxDirections--;
				availableDirections[1] = false;
				//dirCheck += " East ";
			}
			// South
			if (currentRoom->GetAdjacentRooms()[2] != nullptr || walls[2])
			{
				maxDirections--;
				availableDirections[2] = false;
				//dirCheck += " South ";
			}
			// West
			if (currentRoom->GetAdjacentRooms()[3] != nullptr || walls[3])
			{
				maxDirections--;
				availableDirections[3] = false;
				//dirCheck += " West ";
			}

			bool isStuck = (maxDirections == 0) ? true : false;

			if (!isStuck) {
				// Get random int from no of available rooms
				int roomDirection = Random::GetRandom(0, 4);
				int clockwise = Random::GetRandom(0, 2);

				//std::cout << std::setw(26) << dirCheck;
				//std::cout << ", rDir(" << roomDirection << "), " << " isStuck: " << isStuck << ", clock: " << clockwise;

				int direction = roomDirection;

				if (clockwise == 0)
				{
					for (int i = roomDirection; i < (roomDirection + 4); i++)
					{
						int j = (i >= 4) ? (i - 4) : i;
						if ((j == direction && availableDirections[j] == false) || (j == direction && walls[j] == true))
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
						if ((j == direction && availableDirections[j] == false) || (j == direction && walls[j] == true))
						{
							if (direction <= 0)
								direction = 3;
							else
								direction -= 1;
						}
					}
				}

				Room::IRoom* newRoom;
				int x = currentRoom->GetX() + ((direction == 1 || direction == 3) ? ((direction == 1) ? 1 : -1) : 0);
				int y = currentRoom->GetY() + ((direction == 0 || direction == 2) ? ((direction == 2) ? 1 : -1) : 0);

				//std::cout << ", dir: " << direction;
				//std::cout << " X: " << x << " Y: " << y ;

				if (_locations[y * _width + x]->GetRealIcon() == '.' ) {
					newRoom = new Room::Room('N', x, y);
					if (Globals::PRERENDERFOES) {
						((Room::Room*)newRoom)->ChanceSpawnRandomEnemies(this->_enemies, this->_level, 4);
					}
					if (_locations[y * _width + x])
						delete _locations[y * _width + x]; // delete room.
					_locations[y * _width + x] = newRoom;
				}
				else {
					newRoom = _locations[y * _width + x];
				}

				// Link current room with last room and back
				((Room::Room*)currentRoom)->AddAdjacentRoom(newRoom, direction);
				((Room::Room*)newRoom)->AddAdjacentRoom(currentRoom, (direction > 1) ? direction - 2 : direction + 2);

			}
		}
		createExtraPath(percentage, ++roomIndex, tempList);
	}
	
	const std::string Level::GetLevelAsString() const
	{
		std::string level = "";

		level.append(std::to_string(_startPoint->GetX())).append(";");		// Startpoint X
		level.append(std::to_string(_startPoint->GetY())).append(";");		// Startpoint Y
		level.append(std::to_string(_endPoint->GetX())).append(";");		// EndPoint Y
		level.append(std::to_string(_endPoint->GetY())).append(";");		// EndPoint Y
		level.append("[");
		for (unsigned int i = 0; i < _locations.size(); i++)
		{
			level.append(std::to_string(_locations[i]->GetRealIcon())).append(";");
			level.append(std::to_string(_locations[i]->IsDiscovered()));
			if (i < (_locations.size() - 1))
				level.append(",");
		}
		level.append("]");

		return level;
	}


	Level::Level(const Level& other)
		: _startPoint{ std::move(other._startPoint) }
		, _endPoint{ std::move(other._endPoint) }
		, _locations{ std::move(other._locations) }
	{
	}
	Level::Level(Level&& other)
		: _startPoint{ std::move(other._startPoint) }
		, _endPoint{ std::move(other._endPoint) }
		, _locations{ std::move(other._locations) }
	{
		other._startPoint = nullptr;
		other._endPoint = nullptr;
		other._locations.clear();
	}
	Level& Level::operator=(const Level& other)
	{
		if (this != &other)
		{
			if (_startPoint)
				delete _startPoint;
			if (_endPoint)
				delete _endPoint;
			if (!_locations.empty()) {
				for (unsigned int i = 0; i < _locations.size(); i++)
					delete _locations[i];
				_locations.clear();
			}

			Level copy{ std::move(other) };

			std::swap(*this, copy);
		}
		return *this;
	}
	Level& Level::operator=(Level&& other)
	{
		if (this != &other)
		{
			if (_startPoint)
				delete _startPoint;
			if (_endPoint)
				delete _endPoint;
			if (!_locations.empty()) {
				for (unsigned int i = 0; i < _locations.size(); i++)
					delete _locations[i];
				_locations.clear();
			}

			std::swap(_startPoint, other._startPoint);
			std::swap(_endPoint, other._endPoint);
			std::swap(_locations, other._locations);

			other._startPoint = nullptr;
			other._endPoint = nullptr;
			other._locations.clear();
		}
		return *this;
	}

} }