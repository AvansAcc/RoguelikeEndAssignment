#include "StairsRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	StairsRoom::StairsRoom(char icon, bool isDirectionDown) 
		: Room(icon)
	{
		this->_isDirectionDown = isDirectionDown;
		this->_isDiscovered = false;
	}
	
	const bool StairsRoom::IsDirectionDown()
	{
		return this->_isDirectionDown;
	}

} } }