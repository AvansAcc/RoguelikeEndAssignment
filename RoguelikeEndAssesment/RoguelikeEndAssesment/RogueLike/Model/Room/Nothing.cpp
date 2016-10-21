#include "Nothing.h"

namespace RogueLike { namespace Model { namespace Room {

	Nothing::Nothing(char icon, int x, int y) : IRoom(icon, x, y)
	{
		this->_icon = icon;
	}
	Nothing::~Nothing()
	{

	}
	const char Nothing::GetIcon() const
	{
		return this->_icon;
	}
	const char Nothing::GetRealIcon() const
	{
		return this->_icon;
	}

	const int Nothing::GetX() const
	{
		return this->_xpos;
	}
	const int Nothing::GetY() const
	{
		return this->_ypos;
	}

} } }