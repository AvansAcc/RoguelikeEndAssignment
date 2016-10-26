#include "Player.h"

namespace RogueLike { namespace Model {

	Player::Player(std::string name, int x, int y)
	{
		_isDead = false;
		_lifepoints = 100;
		_defence = 0;
		_name = name;
		_icon = 'P';
		_level = 0;
		_xp = 0;
		_attack = 0;
		_items.clear();
		_xpos = x;
		_ypos = y;
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

	const std::string Player::GetVitals()
	{
		std::string returnString = "Statistieken:";
		returnString.append("\nNaam:        " + _name);
		returnString.append("\nLevens:      " + std::to_string(_lifepoints) + "/100");
		returnString.append("\nLevel:       " + std::to_string(_level));
		returnString.append("\nErvaring:    " + std::to_string(_xp) + "/100");
		returnString.append("\nAanval:      " + std::to_string(_attack));
		returnString.append("\nVerdediging: " + std::to_string(_defence));
		return returnString;
	}

	const std::string Player::GetInventory()
	{
		std::string returnString = "Bezittingen: ";
		for each (Item* item in this->_items) {
			returnString.append("\n" + item->Look());
		}
		if (this->_items.size() <= 0) {
			returnString.append("\nJe hebt op dit moment geen bezittingen.");
		}
		return returnString;
	}

	void Player::Heal(int heal)
	{
		_lifepoints += heal;
		if (_lifepoints > 100) {
			_lifepoints = 100;
		}
	}

	void Player::SetNewPlayerLocation(int x, int y) 
	{
		if (x > 1 || x < -1 || y > 1 || y < -1) {
			return;
		}
		_xpos += x;
		_ypos += y;
	}

	void Player::TeleportPlayerLocation(int x, int y)
	{
		_xpos = x;
		_ypos = y;
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

} }