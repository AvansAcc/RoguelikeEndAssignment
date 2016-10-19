#pragma once

#include "IRoom.h"
#include "Nothing.h"
#include <vector>
#include "../Enemy.h"
#include "../Item.h"

namespace RogueLike { namespace Model { namespace Room {
	
	class Room : public IRoom {
	private:
		char _icon;
		//std::vector<IRoom*> _adjacentRooms;
		std::vector<Enemy*> _enemies;
		Item* _item;
	protected:
		bool _isDiscovered;
	public:
		Room(char icon);
		~Room();
		virtual const char GetIcon() const override;
		virtual const bool IsDiscovered();
		virtual void AddItem(Item* item);
		//virtual void AddAdjacentRoom(IRoom* room, int direction);
	};

} } }