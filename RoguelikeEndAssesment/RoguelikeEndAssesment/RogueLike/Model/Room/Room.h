#pragma once

#include "IRoom.h"
#include <iostream>
#include "Nothing.h"
#include <vector>
#include "../Enemy.h"
#include "../Item.h"
#include "../../Variables.h"
#include "../../Utils/File.h"

namespace RogueLike { namespace Model { namespace Room {
	
	class Room : public IRoom {
	private:
		
	protected:
		std::string _description;
		std::string _directionDescription;
		std::vector<IRoom*> _adjacentRooms;
		std::vector<bool> _destroyedCorridors;
		std::vector<Enemy*> _enemies;
		Item* _item;
	public:
		Room(char icon, int x, int y);
		virtual ~Room();
		//Room(const Room& other);
		//Room(Room&& other);
		//Room& operator=(const Room& other);
		//Room& operator=(Room&& other);
		virtual const char GetIcon() const override;
		virtual const char GetRealIcon() const override;
		virtual const int GetX() const override;
		virtual const int GetY() const override;
		virtual const std::vector<IRoom*> GetAdjacentRooms();
		const std::string GetMonsterIcon() const override;
		void SetEnemy(std::vector<Enemy*> enemies);
		virtual const bool HasAdjacentRooms() const;

		virtual std::vector<bool> GetDestroyedCorridors();
		virtual void SetDestroyed(int dir, bool val);
		virtual void SetDestroyedCorridor(const unsigned int index, const bool destroyed);

		virtual Enemy* GetEnemy() const;
		virtual std::vector<Enemy*> GetEnemies() const { return _enemies; };
		virtual const unsigned int GetAmountOfEnemies() const;
		virtual const unsigned int GetAmountOfEnemiesAlive() const;
		virtual Item* GetItem() const;
		virtual const bool IsDiscovered() const override;
		virtual void Discover();

		virtual void AddItem(Item* item);
		virtual void AddAdjacentRoom(IRoom* room, int direction);
		virtual const std::string GetRoomDescription();
		virtual const std::string GetRoomDirectionDescription();
		
		virtual void ChanceSpawnRandomEnemies(std::vector<Enemy*>& enemies, unsigned int currentlevel, int chance);
		virtual void DeleteEnemies();
		virtual void ChanceSpawnRandomItem(std::vector<Item*>& items, unsigned int currentlevel, int chance);
		virtual void RemoveItem(); // Remove the item from room when it is givin to the player.
		virtual void DeleteItem(); // Delete the item
	};

} } }