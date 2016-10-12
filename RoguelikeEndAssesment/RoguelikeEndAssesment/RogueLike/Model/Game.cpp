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


	void Game::Update()
	{

	}


	Game::Game(const Game& other)
	{
		_levelManager = new LevelManager(*other._levelManager);
		_player = new Player(*other._player);
	}
	Game::Game(Game&& other)
	{
		_levelManager = other._levelManager;
		_player = other._player;

		other._levelManager = nullptr;
		other._player = nullptr;
	}

	Game& Game::operator=(const Game& other)
	{
		if (this != &other)
		{
			delete _player;
			delete _levelManager;

			_levelManager = new LevelManager();
			_player = new Player();

			_levelManager = other._levelManager;
			_player = other._player;
		}
		return *this;
	}
	Game& Game::operator=(Game&& other)
	{
		if (this != &other)
		{
			delete _player;
			delete _levelManager;

			_levelManager = other._levelManager;
			_player = other._player;

			other._levelManager = nullptr;
			other._player = nullptr;
		}
		return *this;
	}


} }