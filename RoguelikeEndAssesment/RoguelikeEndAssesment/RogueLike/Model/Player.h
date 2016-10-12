#pragma once

#include "../Common.h"
#include <string>
#include "Item.h"
#include <vector>
#include "../Utils/Random.h"

namespace RogueLike { namespace Model {
	class Player {
	private:
		uint lifepoints;
		uint defence;
		std::string name;
		uint level;
		uint xp;
		uint attack;
		std::vector<Item*> items;
		bool is_dead;
	public:

	private:
	public:
		Player();
		const std::string GetName();
		const char GetIcon();
		const uint Attack();
		void Damage(const uint damage);
	};
} }