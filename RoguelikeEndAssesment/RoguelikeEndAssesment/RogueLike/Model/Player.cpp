#include "Player.h"

namespace RogueLike { namespace Model {

	Player::Player()
	{
		is_dead = false;
		lifepoints = 0;
		defence = 0;
		name = "";
		level = 0;
		xp = 0;
		attack = 0;
		items.clear();
	}

	const std::string Player::GetName()
	{
		return name;
	}
	const char Player::GetIcon()
	{
		return 'P';
	}
	const uint Player::Attack()
	{
		return Random<int>::GetRandom(0, 10 * level);
	}
	void Player::Damage(const uint damage)
	{
		if (lifepoints - damage >= 0)
			lifepoints -= damage;
		else {
			lifepoints = 0;
			is_dead = true;
		}
	}

} }