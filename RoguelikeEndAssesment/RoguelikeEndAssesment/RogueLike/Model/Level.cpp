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
		for (int i = 0; i < (_width * _height); i++)
		{
			n = new Room::Nothing('.');
			_locations.push_back(n);
		}
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
		int randomDungeonLength = Random<int>::GetRandom((int)(maxLength * 0.8), maxLength);
		int startLoc[] = { Random<int>::GetRandom(0, _width - 1) , Random<int>::GetRandom(0, _height - 1) };

		Room::IRoom* r = nullptr;

		// 100% loop
		for (int i = 0; i < randomDungeonLength; i++)
		{
			if (i == 0 && _level == 0) {
				r = new Room::StartRoom('S');
				_locations[(startLoc[1] * _width) + startLoc[0]] = r;
			}
			else if (i == 0) {
				r = new Room::StairsRoom('^', false);
				_locations[(startLoc[1] * _width) + startLoc[0]] = r;
			}
			else if (i == randomDungeonLength && _level == _maxDepth) {
				r = new Room::BossRoom('B');
			}
			else if (i == randomDungeonLength) {
				r = new Room::StairsRoom('v', true);
				//((Room::StairsRoom*)r)->IsDirectionDown = true;
			}
			else {
				r = new Room::Room('R');
				//_locations[i - 1]->AddAdjacentRoom(r);
			}
		}

		// 50% loop
		for (int i = 0; i < _locations.size(); i++)
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
		}
	}

	void Level::createLevelPath(Room::IRoom* previousRoom, Room::IRoom* currentRoom, int dungeonLength) 
	{
		if (dungeonLength < 1) {
			return;
		}
		
		// Check available rooms
		bool availablePos[] = {true, true, true, true};
		int maxDirections = 4;
		// North
		if (currentRoom->GetX() <= _width || previousRoom->GetY() == (currentRoom->GetY() - 1) ||
			typeid(_locations[(currentRoom->GetY() - 1) * _width + currentRoom->GetX()]).name() != typeid(Room::Nothing).name())
		{
			maxDirections--;
			availablePos[0] = false;
		}
		// East
		if ((currentRoom->GetX() % (_width - 1)) == 0 || previousRoom->GetX() == (currentRoom->GetX() + 1) ||
			typeid(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() + 1)]).name() != typeid(Room::Nothing).name())
		{
			maxDirections--;
			availablePos[1] = false;
		}
		// South
		if (currentRoom->GetX >= ((_height - 1) * _width) || previousRoom->GetY() == (currentRoom->GetY() + 1) ||
			typeid(_locations[(currentRoom->GetY() + 1) * _width + currentRoom->GetX()]).name() != typeid(Room::Nothing).name())
		{
			maxDirections--;
			availablePos[2] = false;
		}
		// West
		if ((currentRoom->GetX() % _width) == 0 || previousRoom->GetX() == (currentRoom->GetX() - 1) ||
			typeid(_locations[currentRoom->GetY() * _width + (currentRoom->GetX() - 1)]).name() != typeid(Room::Nothing).name())
		{
			maxDirections--;
			availablePos[3] = false;
		}

		bool isStuck = false;
		if (maxDirections == 0)
		{
			isStuck = true;
			maxDirections = 3;
		}

		// Get random int from no of available rooms
		int roomDirection = Random<int>::GetRandom(0, maxDirections);

		// Set current room in right direction
		int direction = maxDirections;
		for (int i = 0; i < maxDirections; i++)
		{
			if (availablePos[i] == false)
				direction++;
		}

		Room::IRoom* newRoom;
		int x = (direction == 1 || direction == 3) ? ((direction == 1) ? 1 : -1) : 0;
		int y = (direction == 0 || direction == 2) ? ((direction == 2) ? 1 : -1) : 0;
		
		if (isStuck)
		{
			newRoom = _locations[(y * _width) + x];
		}
		else {
			newRoom = new Room::Room('N', x, y);
			dungeonLength--;
		}
		
		// Link current room with last room and back
		((Room::Room*)currentRoom)->AddAdjacentRoom(newRoom, direction);
		((Room::Room*)newRoom)->AddAdjacentRoom(currentRoom, (direction > 1) ? direction - 2 : direction + 2);

		createLevelPath(currentRoom, newRoom, dungeonLength);
	}

} }