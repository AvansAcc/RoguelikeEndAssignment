#pragma once

#include "Room.h"

namespace RogueLike { namespace Model { namespace Room {

	class BossRoom : public Room {
	private:

	public:
		BossRoom(char icon, int x, int y);
		virtual ~BossRoom();
		const std::string GetRoomDescription() override;
		void ChanceSpawnRandomEnemies(std::vector<Enemy*>& enemies, unsigned int currentlevel) override;
	};

} } }