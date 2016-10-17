#include "LevelManager.h"

namespace RogueLike { namespace Model {

	LevelManager::LevelManager()
	{
		level = 0;
		levels.clear();
	}

	LevelManager::~LevelManager()
	{
		if (!levels.empty())
		{
			for (uint i = 0; i < levels.size(); i++)
			{
				delete levels[i]; // free memory
			}
			levels.clear(); // empty list
		}
	}

	void LevelManager::GenerateLevel(int level)
	{
		// TODO: Generate Level
		// TODO: Add Generated level to List
	}

	Level* LevelManager::GetLevel()
	{
		if (levels.empty() || level >= levels.size())
			return nullptr;

		return levels[level];
	}

	void LevelManager::NextLevel()
	{
		this->level++;
		this->GenerateLevel(level);
	}

} }