#pragma once

#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	class StairsRoom : public Room {
	private:
		bool _isDirectionDown;
	public:
		StairsRoom(char icon, bool isDirectionDown);
		const bool IsDirectionDown();
	};

} } }