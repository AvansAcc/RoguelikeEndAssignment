#pragma once

#include <string>
#include "../Common.h"
#include "Player.h"
#include "Enum/ItemType.h"

namespace RogueLike { namespace Model {
	class Player;
	class Item {
	public:
		std::string Name;
		std::string Plural;
		uint Amount;
		uint MaxAmount;
		std::string Description;
		int Effect;
		Enum::ItemType Ability;
	public:
		Item();
		~Item();
		const std::string Use(Player& player);
		const std::string Look();
	};
} }