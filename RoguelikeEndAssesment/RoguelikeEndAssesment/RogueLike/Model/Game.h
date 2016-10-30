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
		bool _hasDefeatedBoss;
		bool _isInCombat;
		std::vector<Enemy*> _enemies;
		std::vector<Item*> _items;
		bool _hasThreat;
	public:

	private:
		Room::Room* GetCurrentPlayerRoom();
		const bool  XpPlayerUp(Player* player, std::vector<Enemy*> enemies);
	public:
		Game();
		virtual ~Game();
		Game(const Game& other);
		Game(Game&& other);
		Game& operator=(const Game& other);
		Game& operator=(Game&& other);

		void Start(uint width, uint height, uint max_levels, std::string name);
		void Load(LevelManager& levelmanager, Player& player);
		const bool Update();
		void LoadEnemiesFile();
		void LoadItemsFile();

		std::string BreadthFirstSearch();
		//void MinSpanningTree();
		void ShortestPathV1();
		//Room::Vertex ShortestPathRec(Room::Room* room);

		std::vector<Enemy*> GetEnemies() { return this->_enemies; }


		const std::vector<std::string> GetAvailableActions();
		const std::vector<std::string> GetGameInfo();
		const std::string GetCombatInfo();
		const std::string GetPlayerVitals() const { return this->_player->GetVitals(); }
		const unsigned int GetLevelWidth() const { return this->_levelManager->GetLevelWidth(); }
		const unsigned int GetLevelHeight() const { return this->_levelManager->GetLevelHeight(); }
		const unsigned int GetMaxDepth() const { return this->_levelManager->GetMaxDepth(); }
		const char* const GetMap();

		const bool MovePlayer(int dir);
		const std::string UseStairs();
		const std::string FleePlayer();
		const std::string PlayerCombatRound();
		const std::string EnemyCombatRound();
		const std::string LookAtPlayerInventory();
		const int GetPlayerItemAmount();
		const std::string UseInventory(int choice);
		const std::string RestPlayer();
		const std::string TakeItem();

		void GameOver();
		void StartCombat();
		void EndCombat();
		const std::string CheckCombatOver();
		const bool IsInCombat() const { return _isInCombat; };
		const bool HasThreat() const { return _hasThreat; };
		
		const std::string GetPlayerVitalsAsString() const;
		const std::string GetLevelsAsString() const;
		const int GetPlayerCurrentLevel() const;
	};
} }