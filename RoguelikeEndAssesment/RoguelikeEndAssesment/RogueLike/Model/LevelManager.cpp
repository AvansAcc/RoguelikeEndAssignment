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

	void LevelManager::Load(unsigned int currentlevel, std::vector<Level*> levels)
	{
		this->_level = currentlevel;
		this->ClearLevels();
		if (levels.empty())
		{
			for (unsigned int i = 0; i < this->_level; i++)
			{
				Level* level = new Level(_width, _height, i, _maxLevels);
				level->GenerateMap();
				this->_levels.push_back(std::move(level)); // use the move constructor
			}
		}
		else {
			this->_levels = levels;
		}
		
		this->SetLevel(this->_level);
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
			this->_currentLevel->GenerateMap();
			this->_levels.push_back(std::move(_currentLevel)); // use the move constructor
		}
	}

	const char* const LevelManager::GetMap(const int player_x, const int player_y) const
	{
		if (_currentLevel != nullptr)
			return this->_currentLevel->GetMap(player_x, player_y);
		return nullptr;
	}

	void LevelManager::NextLevel(bool up)
	{
		if (up) {
			this->_level--;
		}
		else {
			this->_level++;
		}
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
	const unsigned int LevelManager::GetMaxDepth() const
	{
		return _maxLevels;
	}

	const std::string LevelManager::GetLevelsAsString() const
	{
		std::string levels = "";
		levels.append("{");
		for (unsigned int i=0; i<_levels.size(); i++)
		{
			levels.append(this->_levels[i]->GetLevelAsString());
			if (i < (_levels.size() - 1))
				levels.append(",");
		}
		levels.append("}");
		return levels;
	}


	LevelManager::LevelManager(const LevelManager& other)
		: _currentLevel{ other._currentLevel }
		, _levels{ std::move(other._levels) }
	{
	}
	LevelManager::LevelManager(LevelManager&& other)
		: _currentLevel{ other._currentLevel }
		, _levels{ std::move(other._levels) }
	{
		other._currentLevel = nullptr;
		other._levels.clear();
	}
	LevelManager& LevelManager::operator=(const LevelManager& other)
	{
		if (this != &other)
		{
			if (_currentLevel)
				delete _currentLevel;
			if (!_levels.empty()) {
				for(unsigned int i=0; i < _levels.size(); i++)
					delete _levels[i];
				_levels.clear();
			}

			LevelManager copy{ std::move(other) };;

			std::swap(*this, copy);
		}
		return *this;
	}
	LevelManager& LevelManager::operator=(LevelManager&& other)
	{
		if (this != &other)
		{
			if (_currentLevel)
				delete _currentLevel;
			if (!_levels.empty()) {
				for (unsigned int i = 0; i < _levels.size(); i++)
					delete _levels[i];
				_levels.clear();
			}

			std::swap(_currentLevel, other._currentLevel);
			std::swap(_levels, other._levels);

			other._currentLevel = nullptr;
			other._levels.clear();
		}
		return *this;
	}

} }