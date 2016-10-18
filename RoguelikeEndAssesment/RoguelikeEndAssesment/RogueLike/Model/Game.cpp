#include "Game.h"

namespace RogueLike { namespace Model {

	Game::Game()
	{
		_isGameOver = false;
		_levelManager = new LevelManager();
		_player = new Player();
	}

	Game::~Game()
	{
		delete _player;
		delete _levelManager;
	}

	void Game::Start()
	{
		_levelManager->Start();
	}


	void Game::Update()
	{
		// TODO: Update Game
	}
	Level* Game::GetLevel()
	{
		return this->_levelManager->GetLevel();
	}


	Game::Game(const Game& other)
		: _levelManager { other._levelManager }
		, _player { other._player }
	{
		//_levelManager = new LevelManager(*other._levelManager);
		//_player = new Player(*other._player);
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