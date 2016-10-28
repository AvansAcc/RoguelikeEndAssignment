#include "BossRoom.h"

namespace RogueLike { namespace Model { namespace Room {

	BossRoom::BossRoom(char icon, int x, int y)
		: Room(icon, x, y)
	{
		this->_isDiscovered = false;
	}

	BossRoom::~BossRoom()
	{

	}

	const std::string BossRoom::GetRoomDescription() 
	{
		std::string returnString;
		if (!_description.empty()) {
			returnString = _description;
		}
		else {
			returnString = "Je betreed de kamer. Er is iets extreem fout aan deze ruimte, je voelt je aan alle kanten bekeken en al je instincten schreeuwen om weg te rennen.";
			_description = returnString;
		}
		return returnString;
	}

	void BossRoom::ChanceSpawnRandomEnemies(std::vector<Enemy*>& enemies, unsigned int currentlevel, int chance)
	{
		this->DeleteEnemies();
		std::vector<Enemy*> availableEnemies;

		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->Type != Enum::EnemyType::NORMAL)
				availableEnemies.push_back(enemies[i]);
		}

		if (!availableEnemies.empty())
		{
			int chanceEnemy = Random::GetRandom(0, availableEnemies.size());
			Enemy* enemy = nullptr;
			double level_percentage = ((currentlevel+1) * 0.1);
			
			enemy = new Enemy(*availableEnemies[chanceEnemy]);
			enemy->Type = Enum::EnemyType::BOSS;
			enemy->Level = (currentlevel + 1);
			enemy->Lifepoints = (unsigned int)(enemy->Lifepoints * level_percentage);
			enemy->MaxLifePoints = (unsigned int)(enemy->MaxLifePoints * level_percentage);
			enemy->MinDamage = (unsigned int)(enemy->MinDamage * level_percentage);
			enemy->MaxDamage = (unsigned int)(enemy->MaxDamage * level_percentage);

			this->_enemies.push_back(enemy);
		}
	}

} } }