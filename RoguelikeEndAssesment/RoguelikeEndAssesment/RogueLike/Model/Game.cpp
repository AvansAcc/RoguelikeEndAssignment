#include "Game.h"

namespace RogueLike { namespace Model {

	Game::Game()
	{
		_isGameOver = false;
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
		_player = new Player(name);
		_levelManager->Start();
	}

	std::vector<std::string> GetAvailableActions() 
	{
		std::vector<std::string> n;
		return n;
	}

	const bool Game::Update()
	{
		if (_player->isDead() /*|| hasDefeatedBoss */) {
			return true;
		}
		else {
			return false;
		}
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