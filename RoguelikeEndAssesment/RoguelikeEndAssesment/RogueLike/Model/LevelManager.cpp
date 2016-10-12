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
			for (int i = 0; i < levels.size(); i++)
			{
				delete levels[i];
			}
		}
	}

	void LevelManager::GenerateLevel(int level)
	{
		// TODO: Generate Level
	}

	Level* LevelManager::GetLevel()
	{
		if (levels.empty())
			return nullptr;

		for (int i=0; i < levels.size(); i++)
		{
			if (levels[i]->GetLevel() == level)
			{
				return levels[i];
			}
		}
		return nullptr;
	}

} }