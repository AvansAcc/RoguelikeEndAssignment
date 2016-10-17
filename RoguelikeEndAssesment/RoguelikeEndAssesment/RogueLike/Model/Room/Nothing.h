#pragma once

#include "IRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	class Nothing : public IRoom {
	private:
		char _icon;
	public:
		Nothing(char icon);
		const char GetIcon() const override;
	};

} } }