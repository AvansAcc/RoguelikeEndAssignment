#include "Nothing.h"

namespace RogueLike { namespace Model { namespace Room {

	Nothing::Nothing(char icon, int x, int y) : IRoom(icon, x, y)
	{
		this->_icon = icon;
	}

	const char Nothing::GetIcon() const
	{
		return this->_icon;
	}

} } }