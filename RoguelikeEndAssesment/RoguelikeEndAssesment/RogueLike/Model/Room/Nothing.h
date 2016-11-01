#pragma once

#include "IRoom.h"
#include "../../Variables.h"

namespace RogueLike { namespace Model { namespace Room {

	class Nothing : public IRoom {
	private:

	public:
		Nothing(char icon, int x, int y);
		virtual ~Nothing();
		const char GetIcon() const override;
		const char GetRealIcon() const override;
		const int GetX() const override;
		const int GetY() const override;
		const bool IsDiscovered() const override;
		const std::string GetMonsterIcon() const override;
	};

} } }