#pragma once

#include "../Common.h"
#include "../Variables.h"
#include "LevelManager.h"
#include "Player.h"

namespace RogueLike { namespace Model {
	
	class Game {
	private:
		Player* _player;
		LevelManager* _levelManager;
		bool _isGameOver;
		bool _isInCombat;
		std::vector<Enemy*> _enemies;
		std::vector<Item*> _items;
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
		const std::string FleePlayer();
		const std::string PlayerCombatRound();
		const std::string EnemyCombatRound();
		const std::string GetCombatInfo();
		const std::string UseStairs();
		std::string CheckCombatOver();
		void GameOver();
		void StartCombat();
		void EndCombat();
		const std::string LookAtPlayerInventory();
		const std::string RestPlayer();
		const std::string TakeItem();

		const bool IsInCombat() const { return _isInCombat; };
		const bool HasThreat() const { return _hasThreat; };
		const std::string GetPlayerVitals() const { return this->_player->GetVitals(); }
		const unsigned int GetLevelWidth() const { return this->_levelManager->GetLevelWidth(); }
		const unsigned int GetLevelHeight() const { return this->_levelManager->GetLevelHeight(); }
		const unsigned int GetMaxDepth() const { return this->_levelManager->GetMaxDepth(); }
		const char* const GetMap();
		void LoadEnemiesFile();
		void LoadItemsFile();
		const std::string GetPlayerVitalsAsString() const;
		const std::string GetLevelsAsString() const;
		const int GetPlayerCurrentLevel() const;
	};
} }