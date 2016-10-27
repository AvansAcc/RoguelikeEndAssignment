#pragma once

#include <string>
#include "Enum\EnemyType.h"
#include "../Common.h"

namespace RogueLike { namespace Model {
	class Enemy {
	private:
	public:
		std::string Name;
		std::string Plural;
		Enum::EnemyType Type;
		int MaxDamage;
		uint Hitchance;
		uint AmountAttacks;
		uint MinDamage;
		uint Level;
		uint Defence;
		uint Lifepoints;
		uint MaxLifePoints;
	private:
	public:
		Enemy();
		virtual ~Enemy();
		const uint Attack(); // Enemy to player
		void Damage(const uint damage); // player to enemy
		std::string GetStatus(); // status of lifepoints
		const bool IsDead() const;
	};
} }