#include "Item.h"

namespace RogueLike { namespace Model {

	Item::Item(std::string name, uint amount, uint max_amount, std::string description)
	{
		this->_name = name;
		this->_amount = amount;
		this->_maxAmount = max_amount;
		this->_description = description;
	}

	const std::string Item::Look()
	{
		return (_name + " has " + std::to_string(_amount) + " left.");
	}

} }