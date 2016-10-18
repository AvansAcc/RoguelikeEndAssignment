#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	Room::Room(char icon) : IRoom()
	{
		this->_icon = icon;
		this->_adjacentRooms.clear();

		/*Nothing* n;
		for (int i = 0; i < 4; i++)
		{
			n = new Nothing('t');
			_adjacentRooms.push_back(n);
		}*/

		this->_enemies.clear();
		this->_item = nullptr;
		this->_isDiscovered = false;
	}

	Room::~Room()
	{
		for (uint i=0; i < _adjacentRooms.size(); i++)
			delete _adjacentRooms[i];
		_adjacentRooms.clear();

		for (uint i = 0; i < _enemies.size(); i++)
			delete _enemies[i];
		_enemies.clear();

		delete _item;
	}
	const char Room::GetIcon() const
	{
		if (this->_isDiscovered)
			return this->_icon;
		else
			return '.';
	}

	const bool Room::IsDiscovered()
	{
		return this->_isDiscovered;
	}

	void Room::AddItem(Item* item)
	{
		if(this->_item != nullptr)
			delete this->_item;
		
		this->_item = item;
	}
	
	void Room::AddAdjacentRoom(IRoom* room, int direction)
	{
		if (direction < 0 || direction > 3)
			return;

		_adjacentRooms.erase(_adjacentRooms.begin() + direction);
		_adjacentRooms.insert(_adjacentRooms.begin() + direction, room);
	}

} } }