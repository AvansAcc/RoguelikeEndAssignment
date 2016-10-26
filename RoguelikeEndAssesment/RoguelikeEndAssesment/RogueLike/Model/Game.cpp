#include "Game.h"

namespace RogueLike { namespace Model {

	Game::Game()
	{
		_isGameOver = false;
		_isInCombat = false;
		_hasThreat = false;
	}

	Game::~Game()
	{
		if(_player)
			delete _player;
		if(_levelManager)
			delete _levelManager;

		if (!_enemies.empty())
		{
			for (unsigned int i = 0; i < _enemies.size(); i++)
				delete _enemies[i];
			_enemies.clear();
		}
	}

	void Game::Start(uint width, uint height, uint max_levels, std::string name)
	{
		_levelManager = new LevelManager(width, height, max_levels);
		_levelManager->Start();
		_player = new Player(name, _levelManager->GetLevel()->GetStartPoint()->GetX(), _levelManager->GetLevel()->GetStartPoint()->GetY());
		this->GetCurrentPlayerRoom()->Discover();
		this->LoadEnemiesFile();
	}

	std::vector<std::string> Game::GetAvailableActions() 
	{
		std::vector<std::string> options;
		if (_isInCombat) {
			options = *Globals::COMBAT_OPTIONS;
		}
		else {
			options = *Globals::ROOM_OPTIONS;
			if (!this->_hasThreat) {
				options[0] = "";
				options[1] = "";
			}
			if (this->GetCurrentPlayerRoom()->GetItem() == nullptr) {
				options[6] = "";
			}
			if (this->_hasThreat)
			{
				options[6] = "";
				options[7] = "";
				options[8] = "";
			}
		}		
		return options;
	}

	const std::vector<std::string> Game::GetGameInfo() 
	{
		std::vector<std::string> returnValue;
		std::string beschrijving;

		beschrijving = "Beschrijving:\n" + this->GetCurrentPlayerRoom()->GetRoomDescription();
		returnValue.push_back(beschrijving);

		beschrijving = "Richtingen:\n" + this->GetCurrentPlayerRoom()->GetRoomDirectionDescription();
		returnValue.push_back(beschrijving);
		
		beschrijving = "Vijanden:\n";
		if (this->GetCurrentPlayerRoom()->GetAmountOfEnemies() > 0) {
			std::string noOfEnemies = std::to_string(this->GetCurrentPlayerRoom()->GetAmountOfEnemies());
			if (this->_isInCombat) {
				beschrijving.append("Je bent in gevecht met " + noOfEnemies + " " + this->GetCurrentPlayerRoom()->GetEnemy()->Name + ".");
			}
			else {
				beschrijving.append("Er kijken " + std::to_string(this->GetCurrentPlayerRoom()->GetAmountOfEnemies()) + " " + this->GetCurrentPlayerRoom()->GetEnemy()->Name + "je aan.");
			}
		}
		else {
			beschrijving.append("Er zijn geen vijanden in deze kamer");
		}
		returnValue.push_back(beschrijving);

		beschrijving = "Item:\n";
		if (this->GetCurrentPlayerRoom()->GetItem() != nullptr) {
			beschrijving.append("Er ligt een " + this->GetCurrentPlayerRoom()->GetItem()->GetName() + " in de kamer");
		}
		else {
			beschrijving.append("Er liggen geen bruikbare spullen in deze kamer");
		}
		returnValue.push_back(beschrijving);

		return returnValue;
	}

	const bool Game::MovePlayer(int dir)
	{
		Room::Room* r = ((Room::Room*)this->GetCurrentPlayerRoom());
		if (r->GetAdjacentRooms()[dir] == nullptr) {
			return false;
		}

		int x = ((dir == 1 || dir == 3) ? ((dir == 1) ? 1 : -1) : 0);
		int y = ((dir == 0 || dir == 2) ? ((dir == 2) ? 1 : -1) : 0);

		this->_player->SetNewPlayerLocation(x, y);
		this->GetCurrentPlayerRoom()->Discover();
		if (this->GetCurrentPlayerRoom()->GetAmountOfEnemies() > 0)
		{
			this->_hasThreat = true;
		}

		// Chance to spawn enemies in room.
		this->GetCurrentPlayerRoom()->ChanceSpawnRandomEnemies(_enemies);

		return true;
	}

	Room::Room* Game::GetCurrentPlayerRoom()
	{
		return ((Room::Room*)_levelManager->GetLevel()->GetLocations()[(_player->GetY() * _levelManager->GetLevelHeight()) + _player->GetX()]);
	}

	const bool Game::Update()
	{
		if (this->_player->isDead() || this->_isGameOver /*|| hasDefeatedBoss */) {
			this->_isGameOver = true;
		}
		return this->_isGameOver;
	}

	void Game::GameOver()
	{
		this->_isGameOver = true;
	}

	const char* const Game::GetMap()
	{
		return this->_levelManager->GetMap(this->_player->GetX(), this->_player->GetY());
	}

	void Game::LoadEnemiesFile()
	{
		try
		{
			Utils::File f("./Assets/monsters.txt");
			std::string s = f.Read();


			size_t pos = 0;
			std::string delimiter = "]";
			std::vector<std::string> tokens;
			std::string token = "";


			// Remove enters
			while ((pos = s.find("\r\n")) != std::string::npos) { s.erase(pos, 2); }


			// split monsters
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());

				token.erase(0, 1); // Remove [
				tokens.push_back(token);
			}

			for each(std::string monster in tokens)
			{
				Enemy* enemy = new Enemy();
				unsigned int index = 0;
				std::string percentage = "";
				std::string amount_attacks = "";
				std::string min_damage = "";
				std::string max_damage = "";
				while ((pos = monster.find(";")) != std::string::npos)
				{
					token = monster.substr(0, pos);
					monster.erase(0, pos + 1);


					switch (index)
					{
					case 0: // Naam
						enemy->Name = token;
						break;
					case 1: // Level
						if (token == "BAAS")
						{
							enemy->Level = 0;
							enemy->Type = Enum::EnemyType::BOSS;
						}
						else {
							enemy->Level = FromString<int>(token);
							enemy->Type = Enum::EnemyType::NORMAL;
						}
						break;
					case 2: // Aanval
						percentage = token.substr(0, token.find('x'));
						amount_attacks = token.substr(token.find('x') + 1, token.size() - 1);
						enemy->Hitchance = FromString<int>(percentage);
						enemy->AmountAttacks = FromString<int>(amount_attacks);
						break;
					case 3: // Schade
						min_damage = token.substr(0, token.find('-'));
						max_damage = token.substr(token.find('-') + 1, token.size() - 1);
						enemy->MinDamage = FromString<int>(min_damage);
						enemy->MaxDamage = FromString<int>(max_damage);
						break;
					case 4: // Verdediging
						enemy->Defence = FromString<int>(token);
						break;
						//case 5: // Levenspunten
						//	enemy->Lifepoints = FromString<int>(token);
						//	break;
					default:
						break;
					}
					index++;
				}
				enemy->Lifepoints = FromString<int>(monster);
				this->_enemies.push_back(enemy);
			}

		}
		catch (ErrorHandling::FileNotFoundException& e) {
			std::cout << e.what() << std::endl;
		}
	}


	Game::Game(const Game& other)
		: _levelManager { other._levelManager }
		, _player { other._player }
	{
	}
	Game::Game(Game&& other)
		: _levelManager{ other._levelManager }
		, _player{ other._player }
	{
		other._levelManager = nullptr;
		other._player = nullptr;
	}
	Game& Game::operator=(const Game& other)
	{
		if (this != &other)
		{
			if(_player)
				delete _player;
			if(_levelManager)
				delete _levelManager;

			Game copy{ other };

			std::swap(*this, copy);
		}
		return *this;
	}
	Game& Game::operator=(Game&& other)
	{
		if (this != &other)
		{
			if (_player)
				delete _player;
			if (_levelManager)
				delete _levelManager;

			std::swap(_levelManager, other._levelManager);
			std::swap(_player, other._player);

			other._levelManager = nullptr;
			other._player = nullptr;
		}
		return *this;
	}


} }