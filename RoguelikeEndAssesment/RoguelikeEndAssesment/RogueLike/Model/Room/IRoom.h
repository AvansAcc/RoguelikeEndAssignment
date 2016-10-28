#pragma once

#include "../../Common.h"
#include <iostream>

namespace RogueLike { namespace Model { namespace Room {
	
	class IRoom {

	protected:
		char _icon;
		int _xpos, _ypos;
		bool _isDiscovered;
	public:
		IRoom(char icon, int x, int y) : _icon{ icon }, _xpos { x }, _ypos{ y } {}
		virtual ~IRoom() { }
		virtual const char GetIcon() const = 0;
		virtual const char GetRealIcon() const = 0;
		virtual const int GetX() const = 0;
		virtual const int GetY() const = 0;
		virtual const bool IsDiscovered() const = 0;
	};

} } }