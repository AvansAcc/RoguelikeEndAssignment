#pragma once

#include "IRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	class Nothing : public IRoom {
	private:

	public:
		Nothing(char icon, int x, int y);
		const char GetIcon() const override;
	};

} } }