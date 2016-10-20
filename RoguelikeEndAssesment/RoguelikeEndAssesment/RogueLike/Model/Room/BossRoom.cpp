#include "BossRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	BossRoom::BossRoom(char icon, int x, int y)
		: Room(icon, x, y)
	{
		this->_isDiscovered = false;
	}

} } }