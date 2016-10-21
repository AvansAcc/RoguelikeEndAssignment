#pragma once

#include "../Common.h"
#include <iostream>
#include <string>
#include "Item.h"
#include "../Utils/Random.h"

namespace RogueLike { namespace Model {
	
	class Item;
	class Player {
	private:
		uint _lifepoints;
		uint _defence;
		std::string _name;
		uint _level;
		uint _xp;
		uint _attack;
		std::vector<Item*> _items;
		bool _isDead;
	public:

	private:
	public:
		Player();
		virtual ~Player();
		const std::string GetName();
		void SetName(const std::string name);
		const char GetIcon();
		const uint Attack();
		void Damage(const uint damage);
	};
} }