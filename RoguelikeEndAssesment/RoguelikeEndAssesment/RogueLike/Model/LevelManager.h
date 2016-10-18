#pragma once

#include "../Common.h"
#include "Level.h"

namespace RogueLike { namespace Model {
	class LevelManager {
	private:
		uint _level;
		std::vector<Level*> _levels;
	public:

	private:
		void GenerateLevel(int level);
	public:
		LevelManager();
		~LevelManager();
		Level* GetLevel();
		void NextLevel();
		void Start();

		const unsigned int GetLevelWidth() const;
		const unsigned int GetLevelHeight() const;
	};
} }