#pragma once

#include "LevelManager.h"
#include "Player.h"

namespace RogueLike { namespace Model {
	class Game {

	private:
		LevelManager* _levelManager;
		Player* _player;
		bool _isGameOver;
	public:

	private:
	public:
		Game();
		~Game();
		Game(const Game& other);
		Game(Game&& other);
		Game& operator=(const Game& other);
		Game& operator=(Game&& other);

		void Update();

	};
} }