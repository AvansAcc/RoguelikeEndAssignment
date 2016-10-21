#include "StartRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	StartRoom::StartRoom(char icon, int x, int y) 
		: Room(icon, x, y)
	{
		this->_isDiscovered = true;
	}

	StartRoom::~StartRoom()
	{

	}

} } }