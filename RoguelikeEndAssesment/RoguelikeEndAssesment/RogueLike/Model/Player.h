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
		int _xpos, _ypos;
	public:

	private:
	public:
		Player(std::string name, int x, int y);
		virtual ~Player();
		int GetX() const;
		int GetY() const;
		void SetNewPlayerLocation(int x, int y);
		const std::string GetName();
		const char GetIcon();
		const bool isDead();
		const uint Attack();
		void Damage(const uint damage);
	};
} }