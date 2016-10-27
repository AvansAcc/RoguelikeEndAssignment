#include "Item.h"

namespace RogueLike { namespace Model {

	Item::Item()
	{
		this->Name = "";
		this->Plural = "";
		this->Amount = 0;
		this->MaxAmount = 0;
		this->Description = "";

		this->Effect = 0;
		this->Ability = Enum::ItemType::XP;
	}

	Item::~Item()
	{

	}

	const std::string Item::Look()
	{
		return (std::to_string(Amount) + "x " + Name +  ". Maximale hoeveelheid om bij je te dragen is " + std::to_string(Amount));
	}
	const bool Item::Use(Player& player)
	{
		switch (Ability)
		{
		case Enum::ItemType::ATTACK:
			player.SetAttackVital(this->Effect);
			return true;
		case Enum::ItemType::DEFENCE:
			player.SetDefenceVital(this->Effect);
			return true;
		case Enum::ItemType::LIFEPOINTS:
			player.Heal(this->Effect);
			return true;
		case Enum::ItemType::XP:
			player.EarnXP(this->Effect);
			return true;
		case Enum::ItemType::TELEPORT:
			player.Teleport(this->Effect);
			return true;
		default:
			return false;
		}
	}

} }