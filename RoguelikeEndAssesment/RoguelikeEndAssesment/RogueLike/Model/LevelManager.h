#pragma once

#include "../Common.h"
#include "Level.h"

namespace RogueLike { namespace Model {
	class LevelManager {
	private:
		uint _level;
		std::vector<Level*> _levels;
		std::vector<Enemy*> _enemies;
		Level* _currentLevel;
		uint _width;
		uint _height;
		uint _maxLevels;
	public:

	private:
		void SetLevel(unsigned int level);
		void ClearLevels();
	public:
		LevelManager(uint width, uint height, uint max_levels);
		virtual ~LevelManager();
		void LevelManager::setEnemies(std::vector<Enemy*>& enemies) { this->_enemies = enemies; }
		LevelManager(const LevelManager& other);
		LevelManager(LevelManager&& other);
		LevelManager& operator=(const LevelManager& other);
		LevelManager& operator=(LevelManager&& other);

		void NextLevel(bool up);
		void Start();

		const Level* GetCurrentLevel() const { return this->_currentLevel; };
		const unsigned int GetLevel() const { return this->_level; }
		const char* const GetMap(const int player_x, const int player_y) const;
		const std::vector<std::string> const GetMonsterHpMap(const int player_x, const int player_y) const;
		const unsigned int GetLevelWidth() const;
		const unsigned int GetLevelHeight() const;
		const unsigned int GetMaxDepth() const;

		void Load(unsigned int currentlevel, std::vector<Level*> levels = {});

		const std::string GetLevelsAsString() const;
	};
} }