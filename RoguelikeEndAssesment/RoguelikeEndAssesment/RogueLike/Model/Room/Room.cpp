#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	Room::Room(char icon, int x, int y) : IRoom(icon, x, y)
	{
		this->_adjacentRooms.clear();
		for (int i = 0; i < 4; i++)
			this->_adjacentRooms.push_back(nullptr);
		this->_enemies.clear();
		this->_item = nullptr;
		this->_isDiscovered = false;
	}

	Room::~Room()
	{
		if (!_adjacentRooms.empty())
			_adjacentRooms.clear();

		if (!_enemies.empty())
		{
			for (uint i = 0; i < _enemies.size(); i++)
				delete _enemies[i];
			_enemies.clear();
		}

		delete _item;
	}
	const char Room::GetIcon() const
	{
		if (this->IsDiscovered())
			return this->_icon;
		else
			return '.';
	}
	const char Room::GetRealIcon() const
	{
		return this->_icon;
	}

	const int Room::GetX() const
	{
		return this->_xpos;
	}

	const int Room::GetY() const
	{
		return this->_ypos;
	}

	const bool Room::IsDiscovered() const
	{
		if (Globals::DEBUG == true)
			return true;
		else
			return this->_isDiscovered;
	}

	void Room::AddItem(Item* item)
	{
		if(this->_item)
			delete this->_item;
		
		this->_item = item;
	}
	

	void Room::AddAdjacentRoom(IRoom* room, int direction)
	{
		if (direction < 0 || direction > 3)
			return;

		_adjacentRooms.at(direction) = room;
	}

	std::vector<IRoom*> Room::GetAdjacentRooms()
	{
		return _adjacentRooms;
	}

} } }