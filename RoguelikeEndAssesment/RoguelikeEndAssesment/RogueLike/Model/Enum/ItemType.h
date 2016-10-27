#pragma once

namespace RogueLike { namespace Model { namespace Enum {

	enum class ItemType : int {
		ATTACK = 0, 
		DEFENCE = 1, 
		LIFEPOINTS = 2, 
		XP = 3,
		TELEPORT = 4,
		COUNT
	};
} } }