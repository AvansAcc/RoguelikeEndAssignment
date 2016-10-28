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

	void BossRoom::ChanceSpawnRandomEnemies(std::vector<Enemy*>& enemies, unsigned int currentlevel)
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
			int changeAmount = Random::GetRandom(1, 4); // 3
			Enemy* enemy = nullptr;
			double level_percentage = ((currentlevel+1) * 0.1);
			
			for (int i = 0; i < changeAmount; i++)
			{
				enemy = new Enemy(*availableEnemies[chanceEnemy]);
				/*enemy = new Enemy();
				enemy->Name = availableEnemies[chanceEnemy]->Name;
				enemy->Plural = availableEnemies[chanceEnemy]->Plural;
				enemy->Type = Enum::EnemyType::BOSS;
				enemy->Level = availableEnemies[chanceEnemy]->Level;
				enemy->Lifepoints = (unsigned int)(availableEnemies[chanceEnemy]->Lifepoints * level_percentage);
				enemy->MaxLifePoints = (unsigned int)(availableEnemies[chanceEnemy]->MaxLifePoints * level_percentage);
				enemy->AmountAttacks = availableEnemies[chanceEnemy]->AmountAttacks;
				enemy->Defence = (unsigned int)(availableEnemies[chanceEnemy]->Defence * level_percentage);
				enemy->Hitchance = availableEnemies[chanceEnemy]->Hitchance;
				enemy->MinDamage = (unsigned int)(availableEnemies[chanceEnemy]->MinDamage * level_percentage);
				enemy->MaxDamage = (unsigned int)(availableEnemies[chanceEnemy]->MaxDamage * level_percentage);*/
				this->_enemies.push_back(enemy);
			}
		}
	}

} } }