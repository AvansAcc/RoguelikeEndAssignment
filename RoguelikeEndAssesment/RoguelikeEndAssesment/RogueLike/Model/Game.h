#pragma once

#include "LevelManager.h"
#include "Player.h"

namespace RogueLike { namespace Model {
	class Game {

	private:
		LevelManager _levelManager;
		Player _player;
		bool _isGameOver;
	public:

	private:
	public:
		Game();
		void Update();

	};
} }