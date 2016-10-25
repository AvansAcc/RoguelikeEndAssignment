#pragma once

#include <string>
#include "../Common.h"
#include "Player.h"

namespace RogueLike { namespace Model {
	
	class Item {
	private:
		std::string _name;
		uint _amount;
		uint _maxAmount;
		std::string _description;
	public:
		Item(std::string name, uint amount, uint max_amount, std::string description);
		//bool Use(Player& player);
		const std::string Look();
		const std::string GetName() { return this->_name; };
		const std::string GetDescription() { return this->_description; };
		const uint GetMaxAmount() { return this->_maxAmount; };
	};
} }