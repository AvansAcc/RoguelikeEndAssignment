#pragma once

#include "../Common.h"
#include "Level.h"

namespace RogueLike { namespace Model {
	class LevelManager {
	private:
		uint level;
		std::vector<Level*> levels;
	public:

	private:
		void GenerateLevel(int level);
	public:
		LevelManager();
		~LevelManager();
		Level* GetLevel();
		void NextLevel();
	};
} }