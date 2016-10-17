#include "BossRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	BossRoom::BossRoom(char icon)
		: Room(icon)
	{
		this->_isDiscovered = false;
	}

} } }