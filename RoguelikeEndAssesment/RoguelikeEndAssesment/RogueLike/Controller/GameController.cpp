#include "GameController.h"

namespace RogueLike { namespace Controller {

	GameController::GameController()
	{
		_viewController = new ViewController();
	}

	GameController::~GameController()
	{
		delete _viewController;
	}




	// Copy constructor
	GameController::GameController(const GameController& other)
	{
		_viewController = new Controller::ViewController(*other._viewController);
	}

	// Copy assignment operator
	GameController& GameController::operator=(const GameController& other)
	{
		if (this != &other)
		{
			delete _viewController;

			_viewController = new Controller::ViewController();

			_viewController = other._viewController;
			//std::memcpy(_gameController, other._gameController, std::size_t (_gameController));
		}
		return *this;
	}


	// Move constructor
	GameController::GameController(GameController&& other)
	{
		_viewController = other._viewController;
		other._viewController = nullptr;
	}

	// Move assignment operator
	GameController& GameController::operator=(GameController&& other)
	{
		if (this != &other)
		{
			delete _viewController;

			_viewController = other._viewController;

			other._viewController = nullptr;
		}
		return *this;
	}

} }