#pragma once

#include <string>
#include "../Common.h"
#include "Player.h"

namespace RogueLike { namespace Model {
	
	class Item {
	private:
		std::string name;
		uint amount;
		const uint max_amount;
	public:
		Item(std::string name, uint amount, uint max_amount);
		//bool Use(Player& player);
		std::string Look();
		std::string GetDescription();
	};
} }