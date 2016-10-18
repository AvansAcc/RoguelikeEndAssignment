#pragma once

#include "LevelManager.h"
#include "Player.h"

namespace RogueLike { namespace Model {
	class Game {

	private:
		Player* _player;
		LevelManager* _levelManager;
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

		void Start(uint width, uint height, uint max_levels);
		void Update();

		const unsigned int GetLevelWidth() const { return this->_levelManager->GetLevelWidth(); }
		const unsigned int GetLevelHeight() const { return this->_levelManager->GetLevelHeight(); }

		char* GetMap();
	};
} }