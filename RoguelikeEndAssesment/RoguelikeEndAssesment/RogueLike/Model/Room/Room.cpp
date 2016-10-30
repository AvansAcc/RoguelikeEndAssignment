#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	Room::Room(char icon, int x, int y) : IRoom(icon, x, y)
	{
		this->_adjacentRooms.clear();
		for (int i = 0; i < 4; i++)
			this->_adjacentRooms.push_back(nullptr);
		/*this->_adjacentVertices.clear();
		for (int i = 0; i < 4; i++)
			this->_adjacentVertices.push_back(nullptr);*/
		for (int i = 0; i < 4; i++)
			this->_destroyedCorridors.push_back(false);
		this->_enemies.clear();
		this->_item = nullptr;
		this->_isDiscovered = false;
	}

	Room::~Room()
	{
		if (!_adjacentRooms.empty())
			_adjacentRooms.clear();
		this->DeleteEnemies();
		this->DeleteItem();
	}
	void Room::DeleteEnemies()
	{
		if (!_enemies.empty()) {
			for (unsigned int i = 0; i < _enemies.size(); i++)
				delete _enemies[i];
			_enemies.clear();
		}
	}
	void Room::DeleteItem() // If player doesn't picks item up
	{
		if (this->_item)
			delete _item;
		this->_item = nullptr;
	}
	void Room::RemoveItem() // If player picks item up
	{
		this->_item = nullptr;
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

	const std::vector<bool> Room::GetDestroyedCorridors()
	{
		return _destroyedCorridors;
	}

	Enemy* Room::GetEnemy() const
	{
		for (unsigned int i=0; i < _enemies.size(); i++)
		{
			if (!_enemies[i]->IsDead())
				return _enemies[i];
		}
		return nullptr;
	}

	const unsigned int Room::GetAmountOfEnemies() const
	{
		return (unsigned int)_enemies.size();
	}
	
	const unsigned int Room::GetAmountOfEnemiesAlive() const
	{
		unsigned int amount = 0;
		for each(Enemy* e in _enemies)
		{
			if (!e->IsDead())
				amount++;
		}
		return amount;
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
	void Room::SetVertex(unsigned int index, Vertex* v)
	{
		if (index < 0 || index > 4)
			return;
		if (_adjacentVertices.at(index))
			delete _adjacentVertices.at(index);

		_adjacentVertices.at(index) = v;
	}

	const bool Room::HasAdjacentVertices() const
	{
		bool hasVertex = false;
		for each(Vertex* v in this->_adjacentVertices)
		{
			if (v != nullptr)
				hasVertex = true;

		}
		return hasVertex;
	}

	void Room::DeleteAllVertices()
	{
		for (unsigned int i=0; i < this->_adjacentVertices.size(); i++)
		{
			if (this->_adjacentVertices[i] != nullptr)
			{
				delete this->_adjacentVertices[i];
				this->_adjacentVertices[i] = nullptr;
			}
		}
	}

	void Room::DeleteVertex(unsigned int index)
	{
		if (index < 0 || index > 4)
			return;
		delete this->_adjacentVertices.at(index);
		this->_adjacentVertices.at(index) = nullptr;
	}

	const bool Room::HasAdjacentRooms() const
	{
		bool hasRooms = false;
		for each(IRoom* r in this->_adjacentRooms)
		{
			if (r != nullptr && dynamic_cast<Room*>(r) != nullptr)
				hasRooms = true;
		}
		return hasRooms;
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
			std::vector<std::string> cleanesses{ "opgeruimde", "bebloede", "zwartgeblakerde" };
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

		//int e = 10;
		//for each (Enemy* foe in ((Room*)room)->GetEnemies()) {
		//	e += foe->MaxLifePoints;
		//}
		//Vertex* n = new Vertex;
		//n->Room = ((Room*)room);
		//n->weight = e;
		//n->shortestDir = direction;

		//_adjacentVertices.at(direction) = n;
	}
	void Room::ChanceSpawnRandomEnemies(std::vector<Enemy*>& enemies, unsigned int currentlevel, int chance)
	{
		if (chance > 10) {
			chance = 10;
		}
		std::vector<Enemy*> availableEnemies;

		for (unsigned int i=0; i < enemies.size(); i++)
		{
			if ((int)enemies[i]->Level >= ((int)currentlevel-2) && (int)enemies[i]->Level <= ((int)currentlevel+1))
			{
				if(enemies[i]->Type != Enum::EnemyType::BOSS)
					availableEnemies.push_back(enemies[i]);
			}
		}

		int chanceSpawn = Random::GetRandom(1, 11);
		if (chanceSpawn <= chance && !availableEnemies.empty())
		{
			int chanceEnemy = Random::GetRandom(0, (int)availableEnemies.size());
			int changeAmount = Random::GetRandom(1, 4); // 3
			Enemy* enemy = nullptr;

			for (int i = 0; i < changeAmount; i++)
			{
				enemy = new Enemy(*availableEnemies[chanceEnemy]); // use the copy constructor
				this->_enemies.push_back(enemy);
			}
		}
	}

	void Room::ChanceSpawnRandomItem(std::vector<Item*>& items, unsigned int currentlevel, int chance)
	{
		if (chance > 10) {
			chance = 10;
		}
		int chanceSpawn = Random::GetRandom(0, 10);
		if (chanceSpawn <= chance && !items.empty())
		{
			Item* item = nullptr;
			int chanceItem = Random::GetRandom(0, (int)items.size());

			item = new Item(*items[chanceItem]); // use the copy constructor
			item->Amount = 1;
			this->AddItem(item);
		}
	}

} } }