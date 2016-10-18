#include "Level.h"

namespace RogueLike { namespace Model {

	Level::Level(int width, int height, int depth, int maxdepth) 
	{
		this->_width = width;
		this->_height = height;
		this->_level = depth;
		this->_maxDepth = maxdepth;
		this->_locations.clear();
		GenerateMap();
	}

	char* Level::GetMap(const int w, const int h)
	{
		// TODO: Generate Level Map
		return nullptr;
	}

	void Level::GenerateMap()
	{
		int maxLength = _width + _height;
		int randomDungeonLength = Random<int>::GetRandom((int)(maxLength * 0.8), maxLength);
		
		int startLoc[] = { Random<int>::GetRandom(0, _width - 1) , Random<int>::GetRandom(0, _height - 1) };

		Room::Room* r;
		// 100% loop
		for (int i = 0; i < randomDungeonLength; i++)
		{
			if (i == 0 && _level == 0) {
				r = new Room::StartRoom('S');
			}
			else if (i == 0) {
				r = new Room::StairsRoom('^', false);
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

			int direction = Random<int>::GetRandom(0, 3);

			_locations.push_back(r);
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
			if ((Random<int>::GetRandom(0, 4)) == 0) {

			}
		}

		/*_locations = std::vector<Room::IRoom*>(_width * _height);

		for (uint i=0; i < _locations.size(); i++)
		{
			_locations[i] = new Room::Room('R');
		}

		int x = 5, y = 5;
		Room::IRoom* answer = _locations[y * _width + x];*/

		/*for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				std::cout << ". ";
			}
			std::cout << std::endl << std::endl;
		}*/
	}

	int Level::checkAdjacentRooms(Room::IRoom*)
	{

		return 0;
	}

} }