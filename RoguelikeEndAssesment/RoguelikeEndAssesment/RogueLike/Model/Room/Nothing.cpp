#include "Nothing.h"

namespace RogueLike { namespace Model { namespace Room {

	Nothing::Nothing(char icon) 
		: IRoom()
	{
		this->_icon = icon;
	}

	const char Nothing::GetIcon() const
	{
		return this->_icon;
	}

} } }