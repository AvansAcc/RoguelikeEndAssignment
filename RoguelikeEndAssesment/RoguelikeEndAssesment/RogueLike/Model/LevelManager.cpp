#include "LevelManager.h"

namespace RogueLike { namespace Model {

	LevelManager::LevelManager(uint width, uint height, uint max_levels)
		: _width {width}
		, _height {height}
		, _maxLevels {max_levels}
		, _level {0}
	{
		
	}

	LevelManager::~LevelManager()
	{
		this->ClearLevels();
		this->_currentLevel = nullptr;
	}

	void LevelManager::Start()
	{
		this->_level = 0;
		this->ClearLevels();
		this->SetLevel(0);
	}

	void LevelManager::ClearLevels()
	{
		if (!_levels.empty())
		{
			for (uint i = 0; i < _levels.size(); i++)
				delete _levels[i]; // free memory
			_levels.clear(); // empty list
		}
	}

	void LevelManager::SetLevel(unsigned int level)
	{
		if (!_levels.empty() && level < _levels.size()) {
			this->_level = level;
			this->_currentLevel = _levels[level];
		} else {
			this->_level = level;
			this->_currentLevel = new Level(_width, _height, level, _maxLevels);
			this->_levels.push_back(_currentLevel);
			this->_currentLevel->GenerateMap();
		}
	}

	const char* const LevelManager::GetMap()
	{
		if (_currentLevel != nullptr)
			return this->_currentLevel->GetMap(this->_width, this->_height);
		return nullptr;
	}

	void LevelManager::NextLevel()
	{
		this->_level++;
		this->SetLevel(_level);
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