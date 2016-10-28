#include "Player.h"

namespace RogueLike { namespace Model {

	Player::Player(std::string name, int x, int y)
	{
		_isDead = false;
		_lifepoints = 100;
		_maxLifepoints = 100;
		_defence = 20;
		_name = name;
		_icon = 'P';
		_level = 1;
		_xp = 0;
		_attack = 1;
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

	void Player::Load(unsigned int level, unsigned int attack, unsigned int defence, unsigned int lifepoints, unsigned int xp, std::vector<Item*> items)
	{
		this->_level = level;
		this->_attack = attack;
		this->_defence = defence;
		this->_lifepoints = lifepoints;
		this->_maxLifepoints = 100 + ((level-1) * 10);
		this->_xp = xp;
		if (!_items.empty())
		{
			for (uint i = 0; i < _items.size(); i++)
				delete _items[i];
			_items.clear();
		}
		this->_items = items;
	}

	const std::string Player::GetVitals()
	{
		std::string returnString = "Statistieken:";
		returnString.append("\nNaam:        " + _name);
		returnString.append("\nLevens:      " + std::to_string(_lifepoints) + "/" + std::to_string(_maxLifepoints));
		returnString.append("\nLevel:       " + std::to_string(_level));
		returnString.append("\nErvaring:    " + std::to_string(_xp) + "/10");
		returnString.append("\nAanval:      " + std::to_string(_attack));
		returnString.append("\nVerdediging: " + std::to_string(_defence));
		return returnString;
	}

	const std::string Player::GetInventory()
	{
		std::string returnString = "Bezittingen: ";
		for (unsigned int i = 0; i < this->_items.size(); i++) {
			returnString.append("\n" + std::to_string(i + 1) + ": " + _items[i]->Look());
		}
		if (this->_items.size() <= 0) {
			returnString.append("\nJe hebt op dit moment geen bezittingen.");
		}
		return returnString;
	}
	bool Player::AddItemToInventory(Item& item)
	{
		bool item_found = false;
		for each(Item* it in _items)
		{
			if (it->Name == item.Name)
			{
				if ((it->Amount + item.Amount) <= it->MaxAmount) {
					it->Amount += item.Amount;
					item_found = true;
					return true; // Add to Existing
				} else
					return false; // Full
			}
		}
		if (!item_found) {
			this->_items.push_back(&item);
			return true; // Add New
		}
		return false;
	}

	const std::string Player::UseItem(uint index)
	{
		if (index < 0 || index >= _items.size())
			return "";

		std::string answer = _items[index]->Use(*this);

		_items[index]->Amount--;

		if (_items[index]->Amount <= 0)
			_items.erase(_items.begin() + index);

		return answer;
	}

	void Player::Heal(int heal)
	{
		_lifepoints += heal;
		if (_lifepoints > _maxLifepoints) {
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
		if (Random::GetRandom(0, 11) <= (10 - (_defence * 0.1)))
		{
			if (damage <= _lifepoints)
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
			if (effect <= (int)this->_attack)
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
			if (effect <= (int)this->_defence)
				this->_defence += effect;
			else
				this->_defence = 0;
		}
		else {
			this->_defence += effect;
		}
	}
	const bool  Player::EarnXP(int effect)
	{
		bool returnBool = false;
		if (effect < 0) {
			if (effect <= (int)this->_xp)
				this->_xp += effect;
			else
				this->_xp = 0;
		}
		else {
			this->_xp += effect;
			if (this->_xp >= 10) {
				this->LevelUp();
				returnBool = true;
				this->_xp = (this->_xp - 10);
			}
		}
		return returnBool;
	}

	void Player::LevelUp()
	{
		this->_level++;
		this->_attack += 5;
		this->_defence += 5;
		this->_maxLifepoints += 10;
		this->_lifepoints = _maxLifepoints;
	}

	void Player::Teleport(int effect)
	{
		if (effect > 0) {
			this->TeleportPlayerLocation(0, 0); // TODO: Teleport to Startpoint?
		} else {
			this->TeleportPlayerLocation(0, 0); // TODO: Teleport to Endpoint?
		}
	}

	const std::string Player::GetVitalsAsString() const
	{
		std::string vitals = "";
		vitals.append("{");
		vitals.append(_name).append(";");						// Name
		vitals.append(std::to_string(_level)).append(";");		// Level
		vitals.append(std::to_string(_xpos)).append(";");		// x POS
		vitals.append(std::to_string(_ypos)).append(";");		// y POS
		vitals.append(std::to_string(_attack)).append(";");		// Attack
		vitals.append(std::to_string(_defence)).append(";");	// Defence
		vitals.append(std::to_string(_xp)).append(";");			// Xp
		vitals.append(std::to_string(_lifepoints));	// Lifepoints
		vitals.append("}");
		vitals.append("{");
		for (unsigned int i = 0; i < _items.size(); i++)
		{
			vitals.append("[");
			vitals.append(_items.at(i)->Name).append(";");
			vitals.append(_items.at(i)->Plural).append(";");
			vitals.append(std::to_string(_items.at(i)->Amount)).append(";");
			vitals.append(std::to_string(_items.at(i)->MaxAmount)).append(";");
			vitals.append(std::to_string(static_cast<int>(_items.at(i)->Ability))).append(";");
			vitals.append(std::to_string(_items.at(i)->Effect)).append(";");
			vitals.append(_items.at(i)->Description);
			vitals.append("]");
		}
		vitals.append("}");
		
		return vitals;
	}

} }