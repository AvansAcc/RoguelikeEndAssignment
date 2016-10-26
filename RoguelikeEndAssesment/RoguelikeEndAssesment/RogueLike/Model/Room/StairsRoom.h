#pragma once

#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	class StairsRoom : public Room {
	private:
		bool _isDirectionDown;
	public:
		StairsRoom(char icon, int x, int y, bool isDirectionDown);
		virtual ~StairsRoom();
		const bool IsDirectionDown();
		const std::string GetRoomDescription() override;
	};

} } }