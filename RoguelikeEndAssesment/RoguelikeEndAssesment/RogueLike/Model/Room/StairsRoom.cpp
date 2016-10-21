#include "StairsRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	StairsRoom::StairsRoom(char icon, int x, int y, bool isDirectionDown) 
		: Room(icon, x, y)
	{
		this->_isDirectionDown = isDirectionDown;
		this->_isDiscovered = false;
	}
	const bool StairsRoom::IsDirectionDown()
	{
		return this->_isDirectionDown;
	}

} } }