#pragma once

#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	class StartRoom : public Room {
	private:
	
	public:
		StartRoom(char icon, int x, int y);
		virtual ~StartRoom();
		const std::string GetRoomDescription() override;
	};

} } }