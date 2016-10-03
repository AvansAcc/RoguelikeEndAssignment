#pragma once

#include <string>
#include "Enum\EnemyType.h"
#include "../Common.h"

namespace RogueLike { namespace Model {
	class Enemy {
	private:
		std::string name;
		EnemyType type;
		int max_damage;
		uint hitchance;
		uint amount_attacks;
		const uint min_damage;
		uint level;
		uint defence;
		uint lifepoints;
	public:

	private:
	public:
		Enemy();
		std::string GetName() { return this->name; }
		const uint Attack(); // Enemy to player
		void Damage(const uint damage); // player to enemy
		std::string GetStatus(); // status of lifepoints
	};
} }