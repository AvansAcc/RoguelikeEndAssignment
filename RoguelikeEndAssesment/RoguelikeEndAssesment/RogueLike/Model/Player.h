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
		char _icon;
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

		int GetX() const { return _xpos; };
		int GetY() const { return _ypos; };
		const std::string GetName() const { return _name; };
		const char GetIcon() const { return _icon; };
		const bool isDead() const { return _isDead; };

		const std::string GetVitals();
		const std::string GetInventory();
		void AddItemToInventory(Item& item);
		void Heal(int heal);
		void SetNewPlayerLocation(int x, int y);
		void TeleportPlayerLocation(int x, int y);
		const uint Attack();
		void Damage(const uint damage);

		void SetAttackVital(int effect);
		void SetDefenceVital(int effect);
		void EarnXP(int effect);
		void Teleport(int effect);
	};
} }