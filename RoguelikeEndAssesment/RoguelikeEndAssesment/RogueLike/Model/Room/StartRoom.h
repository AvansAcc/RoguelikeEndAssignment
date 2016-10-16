#pragma once

#include "Room.h"

namespace RogueLike { namespace Model {

	class StartRoom : public Room {
	private:
		char icon;
	public:
		char GetIcon();
	};
} }