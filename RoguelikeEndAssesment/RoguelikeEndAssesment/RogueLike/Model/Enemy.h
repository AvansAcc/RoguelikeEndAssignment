#pragma once

#include <string>
#include "Enum\EnemyType.h"
#include "../Common.h"

namespace RogueLike { namespace Model {
	class Enemy {
	private:
	public:
		std::string Name;
		Enum::EnemyType Type;
		int MaxDamage;
		uint Hitchance;
		uint AmountAttacks;
		uint MinDamage;
		uint Level;
		uint Defence;
		uint Lifepoints;
	
	private:
	public:
		Enemy();
		const uint Attack(); // Enemy to player
		void Damage(const uint damage); // player to enemy
		std::string GetStatus(); // status of lifepoints
	};
} }