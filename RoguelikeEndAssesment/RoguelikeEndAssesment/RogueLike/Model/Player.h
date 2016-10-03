#pragma once

#include "../Common.h"
#include <string>
#include "Item.h"

namespace RogueLike { namespace Model {
	class Player {
	private:
		uint lifepoints;
		uint defence;
		std::string name;
		uint level;
		uint xp;
		uint attack;
		std::vector<Item> items;

	public:

	private:
	public:
		Player();
		std::string GetName();
		char GetIcon();
		const uint Attack();
		void Damage(const uint damage);
	};
} }