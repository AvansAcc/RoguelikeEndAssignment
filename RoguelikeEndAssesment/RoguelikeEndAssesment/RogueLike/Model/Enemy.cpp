#include "Enemy.h"

namespace RogueLike { namespace Model {

	Enemy::Enemy()
	{
		this->Name = "";
		this->Plural = "";
		this->Level = 0;
		this->Lifepoints = 0;
		this->MaxLifePoints = 0;
		this->Defence = 0;
		this->Hitchance = 0;
		this->MinDamage = 0;
		this->MaxDamage = 0;
		this->AmountAttacks = 0;
		this->Type = Enum::EnemyType::NORMAL;
	}
	Enemy::~Enemy()
	{

	}
	const uint Enemy::Attack()
	{
		if (Random::GetRandom(0, 10) <= (Hitchance * 0.1)) {
			return AmountAttacks * (Random::GetRandom(MinDamage, MaxDamage + 1));
		}
		return 0;
	}
	bool Enemy::Damage(const uint damage)
	{
		if (Random::GetRandom(0, 10) <= (10 - (Defence * 0.1)))
		{
			if (damage <= this->Lifepoints)
				this->Lifepoints -= damage;
			else
				this->Lifepoints = 0;
			return true;
		}
		return false;

	}

	const bool Enemy::IsDead() const
	{
		return (this->Lifepoints <= 0);
	}

	std::string Enemy::GetStatus()
	{
		return this->Name + " has " + std::to_string(this->Lifepoints) + " lifepoints left.";
	}

} }