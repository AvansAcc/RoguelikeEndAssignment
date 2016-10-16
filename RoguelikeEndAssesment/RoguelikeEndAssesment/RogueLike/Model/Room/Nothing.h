#pragma once

#include "IRoom.h"

namespace RogueLike { namespace Model {

	class Nothing : public IRoom {
	private:
		char icon;
	public:
		char GetIcon();
	};
} }