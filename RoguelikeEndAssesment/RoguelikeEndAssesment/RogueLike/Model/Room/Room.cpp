#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	Room::Room(char icon, int x, int y) : IRoom(icon, x, y)
	{
		this->_adjacentRooms.clear();
		for (int i = 0; i < 4; i++)
			this->_adjacentRooms.push_back(nullptr);
		this->_enemy = nullptr;
		this->_item = nullptr;
		this->_isDiscovered = false;
	}

	Room::~Room()
	{
		if (!_adjacentRooms.empty())
			_adjacentRooms.clear();

		delete _enemy;
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

	const std::vector<IRoom*> Room::GetAdjacentRooms()
	{
		return _adjacentRooms;
	}

	const Enemy* Room::GetEnemy() const
	{
		return _enemy;
	}
	const int Room::GetAmountOfEnemies() const
	{
		return amountOfEnemies;
	}

	Item* Room::GetItem() const 
	{
		return _item;
	}

	void Room::Discover()
	{
		_isDiscovered = true;
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

	const std::string Room::GetRoomDescription()
	{
		std::string returnString;
		if (!_description.empty()) {
			returnString = _description;
		}
		else {
			std::string size, cleaness, furniture;
			int choice;
			std::vector<std::string> sizes{ "kleine", "middelgrote", "grote" };
			std::vector<std::string> cleanesses{ "opgeruimde", "bebloede", "zwartgeblankende" };
			std::vector<std::string> furnitures{ " met in het midden van de ruimte een tafel met 4 stoelen.", " met een bed in de hoek van de ruimte.", ", de ruimte is compleet leeg." };

			choice = Random::GetRandom(0, 3);
			size = sizes[choice];
			choice = Random::GetRandom(0, 3);
			cleaness = cleanesses[choice];
			choice = Random::GetRandom(0, 3);
			furniture = furnitures[choice];

			returnString = "Je betreed de kamer. Het is een " + size + " " + cleaness + " ruimte" + furniture;
			_description = returnString;
		}
		return returnString;
	}
	
	const std::string Room::GetRoomDirectionDescription()
	{
		std::string returnString;
		if (!_directionDescription.empty()) {
			returnString = _directionDescription;
		}
		else {
			std::string direction;
			returnString = "Er is een gang in de volgende richtingen: {";
			bool firstCorridor = true;
			for (unsigned int i = 0; i < _adjacentRooms.size(); i++)
			{
				switch (i)
				{
					case 0:
						direction = "noord";
							break;
					case 1:
						direction = "oost";
						break;
					case 2:
						direction = "zuid";
						break;
					case 3:
						direction = "west";
						break;
				}
				if (_adjacentRooms[i] != nullptr) {
					if (firstCorridor) {
						returnString.append(direction);
						firstCorridor = false;
					}
					else {
						returnString.append(" | " + direction);
					}
				}
			}
			returnString.append("}. Voor de rest zijn er alleen muren");
			_directionDescription = returnString;
		}
		return returnString;
	}

	void Room::AddAdjacentRoom(IRoom* room, int direction)
	{
		if (direction < 0 || direction > 3)
			return;

		_adjacentRooms.at(direction) = room;
	}

} } }