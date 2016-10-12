#pragma once

#include "Level.h"
#include <vector>

namespace RogueLike { namespace Model {
	class LevelManager {
	private:
		int level;
		std::vector<Level*> levels;
	public:

	private:
		void GenerateLevel(int level);
	public:
		LevelManager();
		~LevelManager();
		Level* GetLevel();
	};
} }