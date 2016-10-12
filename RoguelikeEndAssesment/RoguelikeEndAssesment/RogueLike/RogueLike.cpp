#include "RogueLike.h"

namespace RogueLike {

	RogueLike::RogueLike()
	{
		_gameController = new Controller::GameController();
	}
	RogueLike::~RogueLike()
	{
		delete _gameController;
	}
	
	void RogueLike::Start()
	{
		// TODO: Start the game
	}


	// Copy constructor
	RogueLike::RogueLike(const RogueLike& other)
	{
		_gameController = new Controller::GameController(*other._gameController);
	}

	// Copy assignment operator
	RogueLike& RogueLike::operator=(const RogueLike& other)
	{
		if (this != &other)
		{
			delete _gameController;

			_gameController = new Controller::GameController();

			_gameController = other._gameController;
			//std::memcpy(_gameController, other._gameController, std::size_t (_gameController));
		}
		return *this;
	}


	// Move constructor
	RogueLike::RogueLike(RogueLike&& other)
	{
		_gameController = other._gameController;
		other._gameController = nullptr;
	}

	// Move assignment operator
	RogueLike& RogueLike::operator=(RogueLike&& other)
	{
		if (this != &other)
		{
			delete _gameController;

			_gameController = other._gameController;

			other._gameController = nullptr;
		}
		return *this;
	}
}