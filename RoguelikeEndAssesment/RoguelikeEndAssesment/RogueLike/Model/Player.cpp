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
	void Player::AddItemToInventory(Item& item)
	{
		this->_items.push_back(&item);
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
		return this->_attack;
	}
	bool Player::Damage(const uint damage)
	{
		if (Random::GetRandom(0, 10) <= (_defence * 0.1))
		{
			if ((_lifepoints - damage) >= 0)
				_lifepoints -= damage;
			else {
				_lifepoints = 0;
				_isDead = true;
			}
			return true;
		}
		return false;
	}

	void Player::SetAttackVital(int effect)
	{
		if (effect < 0) {
			if (this->_attack - effect >= 0)
				this->_attack += effect;
			else
				this->_attack = 0;
		}
		else {
			this->_attack += effect;
		}
	}
	void Player::SetDefenceVital(int effect)
	{
		if (effect < 0) {
			if (this->_defence - effect >= 0)
				this->_defence += effect;
			else
				this->_defence = 0;
		}
		else {
			this->_defence += effect;
		}
	}
	void Player::EarnXP(int effect)
	{
		if (effect < 0) {
			if (this->_xp - effect >= 0)
				this->_xp += effect;
			else
				this->_xp = 0;
		}
		else {
			this->_xp += effect;
		}
	}

	void Player::Teleport(int effect)
	{
		if (effect > 0) {
			this->TeleportPlayerLocation(0, 0); // TODO: Teleport to Startpoint?
		} else {
			this->TeleportPlayerLocation(0, 0); // TODO: Teleport to Endpoint?
		}
	}

} }