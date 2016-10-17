#include "Enemy.h"

namespace RogueLike { namespace Model {

	Enemy::Enemy()
	{

	}

	const uint Enemy::Attack()
	{
		// TODO: Enemy Attack
		return 0;
	}
	void Enemy::Damage(const uint damage)
	{
		// TODO: Enemy take Damage
	}

	std::string Enemy::GetStatus()
	{
		return this->Name + " has " + std::to_string(this->Lifepoints) + " lifepoints left.";
	}

} }