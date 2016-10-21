#pragma once

#include "IRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	class Nothing : public IRoom {
	private:

	public:
		Nothing(char icon, int x, int y);
		const char GetIcon() const override;
		const char GetRealIcon() const override;
		const int GetX() const override;
		const int GetY() const override;
	};

} } }