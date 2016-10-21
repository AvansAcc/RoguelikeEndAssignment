#pragma once

#include "../../Common.h"
#include <iostream>

namespace RogueLike { namespace Model { namespace Room {
	
	class IRoom {

	protected:
		char _icon;
		int _xpos, _ypos;

	public:
		IRoom(char icon, int x, int y) : _icon{ icon }, _xpos { x }, _ypos{ y } {}
		virtual ~IRoom() { std::cout << "Destructor: IRoom" << std::endl; }
		virtual const char GetIcon() const = 0;
		virtual const char GetRealIcon() const = 0;
		virtual const int GetX() const = 0;
		virtual const int GetY() const = 0;
	};

} } }