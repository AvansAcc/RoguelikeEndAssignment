#pragma once

#include "Room.h"

namespace RogueLike { namespace Model {

	class StairsRoom : public Room {
	private:
		char icon;
		bool isDirectionDown;
	public:
		char GetIcon();
		bool IsDirectionDown();
	};
} }