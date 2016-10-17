#pragma once

#include "../../Common.h"

namespace RogueLike { namespace Model { namespace Room {
	
	class IRoom {

	public:
		virtual const char GetIcon() const = 0;
	};

} } }