#pragma once

#include "Room.h"

namespace RogueLike { namespace Model {

	class BossRoom : public Room {
	private:
		char icon;
	public:
		const char GetIcon() const override;

	};
} }