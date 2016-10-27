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
		this->Type = Enum::EnemyType::NORMAL;
	}
	Enemy::~Enemy()
	{

	}
	const uint Enemy::Attack()
	{
		// TODO: Enemy Attack
		return 0;
	}
	void Enemy::Damage(const uint damage)
	{
		if (this->Lifepoints - damage >= 0)
			this->Lifepoints -= damage;
		else
			this->Lifepoints = 0;
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