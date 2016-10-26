#include "Game.h"

namespace RogueLike { namespace Model {

	Game::Game()
	{
		_isGameOver = false;
		_isInCombat = false;
	}

	Game::~Game()
	{
		if(_player)
			delete _player;
		if(_levelManager)
			delete _levelManager;
	}

	void Game::Start(uint width, uint height, uint max_levels, std::string name)
	{
		_levelManager = new LevelManager(width, height, max_levels);
		_levelManager->Start();
		_player = new Player(name, _levelManager->GetLevel()->GetStartPoint()->GetX(), _levelManager->GetLevel()->GetStartPoint()->GetY());
		this->GetCurrentPlayerRoom()->Discover();
	}

	std::vector<std::string> Game::GetAvailableActions() 
	{
		std::vector<std::string> options;
		if (_isInCombat) {
			options = Globals::COMBAT_OPTIONS;
		}
		else {
			options = Globals::ROOM_OPTIONS;
			if (this->GetCurrentPlayerRoom()->GetItem() == nullptr) {
				options[6] = "";
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

		return true;
	}

	Room::Room* Game::GetCurrentPlayerRoom()
	{
		return ((Room::Room*)_levelManager->GetLevel()->GetLocations()[(_player->GetY() * _levelManager->GetLevelHeight()) + _player->GetX()]);
	}

	const bool Game::Update()
	{
		if (_player->isDead() /*|| hasDefeatedBoss */) {
			_isGameOver = true;
		}
		return _isGameOver;
	}

	const char* const Game::GetMap()
	{
		return this->_levelManager->GetMap();
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