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
		std::vector<IRoom*> _adjacentRooms;
		std::vector<Enemy*> _enemies;
		Item* _item;
	protected:
		bool _isDiscovered;
	public:
		Room(char icon, int x, int y);
		virtual ~Room();
		//void setRoom(int percentage, Room::IRoom* previousRoom);
		virtual const char GetIcon() const override;
		virtual const char GetRealIcon() const override;
		virtual const int GetX() const override;
		virtual const int GetY() const override;
		virtual const bool IsDiscovered();
		virtual void AddItem(Item* item);
		virtual void AddAdjacentRoom(IRoom* room, int direction);
		std::vector<IRoom*> GetAdjacentRooms();
	};

} } }