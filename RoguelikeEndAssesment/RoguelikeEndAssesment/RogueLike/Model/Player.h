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
		friend class GameController;
		uint _lifepoints;
		uint _maxLifepoints;
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
		void LevelUp();
	public:
		Player(std::string name, int x, int y);
		virtual ~Player();

		int GetX() const { return _xpos; };
		int GetY() const { return _ypos; };
		const std::string GetName() const { return this->_name; };
		const uint GetHp() const { return this->_lifepoints; }
		const uint GetMaxHp() const { return this->_maxLifepoints; }
		const uint GetLvl() const{ return this->_level; }
		const char GetIcon() const { return this->_icon; };
		const bool isDead() const { return this->_isDead; };

		const std::string GetVitals();
		const std::string GetInventory();
		bool AddItemToInventory(Item& item);
		void Heal(int heal);
		void SetNewPlayerLocation(int x, int y);
		void TeleportPlayerLocation(int x, int y);
		const uint Attack();
		bool Damage(const uint damage);
		void UseItem(uint index);

		void SetAttackVital(int effect);
		void SetDefenceVital(int effect);
		const bool EarnXP(int effect);
		void Teleport(int effect);
		const std::string GetVitalsAsString() const;
	};
} }