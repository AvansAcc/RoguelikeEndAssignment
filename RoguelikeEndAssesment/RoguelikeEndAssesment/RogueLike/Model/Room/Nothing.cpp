#include "Nothing.h"

namespace RogueLike { namespace Model { namespace Room {

	Nothing::Nothing(char icon, int x, int y) : IRoom(icon, x, y)
	{
		this->_icon = icon;
		this->_isDiscovered = false;
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

	const bool Nothing::IsDiscovered() const
	{
		if (Globals::DEBUG == true)
			return true;
		else
			return this->_isDiscovered;
	}

	const std::string Nothing::GetMonsterIcon() const
	{
		return "..";
	}

} } }