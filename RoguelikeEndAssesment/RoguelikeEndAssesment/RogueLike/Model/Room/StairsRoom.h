#pragma once

#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	class StairsRoom : public Room {
	private:
		bool _isDirectionDown;
	public:
		StairsRoom(char icon, int x, int y, bool isDirectionDown);
		const bool IsDirectionDown();
	};

} } }