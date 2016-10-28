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
		return (std::to_string(Amount) + "/" + std::to_string(MaxAmount) + " " + Name + ". {Beschrijving: " + this->Description +" }");
	}
	const std::string Item::Use(Player& player)
	{
		switch (Ability)
		{
		case Enum::ItemType::ATTACK:
			player.SetAttackVital(this->Effect);
			return "Je voelt je sterker dan ooit!";
		case Enum::ItemType::DEFENCE:
			player.SetDefenceVital(this->Effect);
			return "Je voelt je beter dan ooit!";
		case Enum::ItemType::LIFEPOINTS:
			player.Heal(this->Effect);
			return "Je voelt je verwondingen weggaan!";
		case Enum::ItemType::XP:
			player.EarnXP(this->Effect);
			return "Je ervaard allerlei nieuwe belevenissen en gedachten!";
		case Enum::ItemType::TELEPORT:
			player.Teleport(this->Effect);
			return "Je wordt weggetrokken uit de kamer en bent plotseling ergens anders";
		default:
			return "";
		}
	}

} }