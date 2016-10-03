#pragma once

#include "IRoom.h"
#include <vector>
#include "../Enemy.h"
#include "../Item.h"

namespace RogueLike { namespace Model {
	
	class Room : public IRoom {
	private:
		char icon;
		std::vector<IRoom> adjacent_rooms;
		std::vector<Enemy> enemies;
		Item item;
	public:
		Room();
		char GetIcon();
		virtual const bool IsDiscovered();
	};
} }