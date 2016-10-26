#pragma once

#include "LevelManager.h"
#include "Player.h"
#include "../Variables.h"

namespace RogueLike { namespace Model {
	class Game {

	private:
		Player* _player;
		LevelManager* _levelManager;
		bool _isGameOver;
		bool _isInCombat;
		bool _hasThreat;
	public:

	private:
		Room::Room* GetCurrentPlayerRoom();
	public:
		Game();
		virtual ~Game();
		Game(const Game& other);
		Game(Game&& other);
		Game& operator=(const Game& other);
		Game& operator=(Game&& other);

		void Start(uint width, uint height, uint max_levels, std::string name);
		const bool Update();

		std::vector<std::string> GetAvailableActions();
		const std::vector<std::string> GetGameInfo();
		const bool MovePlayer(int dir);
		void FleePlayer();
		const std::string UseStairs();
		void GameOver();
		const std::string LookAtPlayerInventory();
		const std::string RestPlayer();

		const bool IsInCombat() const { return _isInCombat; };
		const bool HasThreat() const { return _hasThreat; };
		const std::string GetPlayerVitals() const { return this->_player->GetVitals(); }
		const unsigned int GetLevelWidth() const { return this->_levelManager->GetLevelWidth(); }
		const unsigned int GetLevelHeight() const { return this->_levelManager->GetLevelHeight(); }
		const char* const GetMap();
	};
} }