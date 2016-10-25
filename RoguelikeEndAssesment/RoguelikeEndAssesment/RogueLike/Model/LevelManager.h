#pragma once

#include "../Common.h"
#include "Level.h"

namespace RogueLike { namespace Model {
	class LevelManager {
	private:
		uint _level;
		std::vector<Level*> _levels;
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
		LevelManager(const LevelManager& other);
		LevelManager(LevelManager&& other);
		LevelManager& operator=(const LevelManager& other);
		LevelManager& operator=(LevelManager&& other);

		void NextLevel();
		void Start();

		const char* const GetMap();
		const unsigned int GetLevelWidth() const;
		const unsigned int GetLevelHeight() const;
	};
} }