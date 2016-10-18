#include "LevelManager.h"

namespace RogueLike { namespace Model {

	LevelManager::LevelManager()
	{
		_level = 0;
		_levels.clear();
	}

	LevelManager::~LevelManager()
	{
		if (!_levels.empty())
		{
			for (uint i = 0; i < _levels.size(); i++)
			{
				delete _levels[i]; // free memory
			}
			_levels.clear(); // empty list
		}
	}

	void LevelManager::Start()
	{
		this->_level = 0;
		this->GenerateLevel(0);
	}

	void LevelManager::GenerateLevel(int level)
	{
		// TODO: Generate Level
		// TODO: Add Generated level to List
	}

	Level* LevelManager::GetLevel()
	{
		if (_levels.empty() || _level >= _levels.size())
			return nullptr;

		return _levels[_level];
	}

	void LevelManager::NextLevel()
	{
		this->_level++;
		this->GenerateLevel(_level);
	}

	const unsigned int LevelManager::GetLevelWidth() const 
	{
		if (_levels.empty() || _level >= _levels.size())
			return 0;
		return this->_levels[_level]->GetWidth();
	}

	const unsigned int LevelManager::GetLevelHeight() const
	{
		if (_levels.empty() || _level >= _levels.size())
			return 0;
		return this->_levels[_level]->GetHeight();
	}

} }