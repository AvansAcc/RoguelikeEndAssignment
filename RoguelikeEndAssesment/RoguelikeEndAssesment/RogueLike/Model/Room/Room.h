#pragma once

#include "IRoom.h"
#include <iostream>
#include "Nothing.h"
#include <vector>
#include "../Enemy.h"
#include "../Item.h"
#include "../../Variables.h"

namespace RogueLike { namespace Model { namespace Room {
	
	class Room : public IRoom {
	private:
		
	protected:
		std::string _description;
		std::string _directionDescription;
		std::vector<IRoom*> _adjacentRooms;
		Enemy* _enemy;
		int amountOfEnemies;
		Item* _item;
		bool _isDiscovered;
	public:
		Room(char icon, int x, int y);
		virtual ~Room();
		Room(const Room& other);
		Room(Room&& other);
		Room& operator=(const Room& other);
		Room& operator=(Room&& other);
		virtual const char GetIcon() const override;
		virtual const char GetRealIcon() const override;
		virtual const int GetX() const override;
		virtual const int GetY() const override;
		virtual const std::vector<IRoom*> GetAdjacentRooms();
		virtual const Enemy* GetEnemy() const;
		virtual const int GetAmountOfEnemies() const;
		virtual Item* GetItem() const;
		virtual const bool IsDiscovered() const;
		virtual void Discover();

		virtual void AddItem(Item* item);
		virtual void AddAdjacentRoom(IRoom* room, int direction);
		virtual const std::string GetRoomDescription();
		virtual const std::string GetRoomDirectionDescription();
	};

} } }