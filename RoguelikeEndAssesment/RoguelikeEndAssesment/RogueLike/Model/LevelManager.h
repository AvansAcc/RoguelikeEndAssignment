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
		~LevelManager();
		void NextLevel();
		void Start();

		char* GetMap();
		const unsigned int GetLevelWidth() const;
		const unsigned int GetLevelHeight() const;
	};
} }