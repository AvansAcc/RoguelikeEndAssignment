#include "Room.h"

namespace RogueLike { namespace Model {

	Room::Room() : IRoom()
	{

	}

	const char Room::GetIcon() const
	{
		return '.';
	}

	const bool Room::IsDiscovered()
	{
		return false;
	}

} }