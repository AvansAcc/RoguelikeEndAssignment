#pragma once


namespace RogueLike { namespace Model {
	class IRoom {

	public:
		virtual const char GetIcon() const = 0;
	};
} }