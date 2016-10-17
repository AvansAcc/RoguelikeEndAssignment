#include "StartRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	StartRoom::StartRoom(char icon) 
		: Room(icon)
	{
		this->_isDiscovered = true;
	}

} } }