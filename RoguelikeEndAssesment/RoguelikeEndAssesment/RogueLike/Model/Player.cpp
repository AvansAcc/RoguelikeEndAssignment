#include "Player.h"

namespace RogueLike { namespace Model {

	Player::Player(std::string name)
	{
		_isDead = false;
		_lifepoints = 100;
		_defence = 0;
		_name = name;
		_level = 0;
		_xp = 0;
		_attack = 0;
		_items.clear();
	}
	Player::~Player()
	{
		if (!_items.empty())
		{
			for (uint i = 0; i < _items.size(); i++)
				delete _items[i];
			_items.clear();
		}
	}
		
	const uint Player::Attack()
	{
		return Random::GetRandom(0, 10 * (_level+1));
	}
	void Player::Damage(const uint damage)
	{
		if ((_lifepoints - damage) >= 0)
			_lifepoints -= damage;
		else {
			_lifepoints = 0;
			_isDead = true;
		}
	}

	const char Player::GetIcon()
	{
		return 'P';
	}
	const std::string Player::GetName()
	{
		return _name;
	}

	const bool Player::isDead()
	{
		return _isDead;
	}

} }