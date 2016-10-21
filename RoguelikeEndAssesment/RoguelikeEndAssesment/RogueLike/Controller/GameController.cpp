#include "GameController.h"

namespace RogueLike { namespace Controller {

	GameController::GameController()
	{
		_viewController = new ViewController();
		_game = new Model::Game();

	}

	GameController::~GameController()
	{
		delete _viewController;
		delete _game;
	}

	void GameController::Start()
	{
		this->_viewController->ShowWelcomeScreen();
		//this->_viewController->PressAnyKeyToContinue();

		uint width = this->_viewController->AskInt("Hoeveel kamers in breedte wilt u de kerker hebben?", 25);
		uint height = this->_viewController->AskInt("Hoeveel kamers in lengte wilt u de kerker hebben?", 25);
		uint max_levels = this->_viewController->AskInt("Hoe diep wilt u de kerker hebben?", 10);

		this->_viewController->Say("Bedankt voor je geduld... Laat het avontuur maar beginnen!\n\n");

		//this->_game->Start(width, height, max_levels);
		//char* map = this->_game->GetMap();
		//this->_viewController->ShowMap(map, this->_game->GetLevelWidth(), this->_game->GetLevelHeight());
		//delete[] map;
	}

	void GameController::Update()
	{
		this->_game->Update();
	}


	// Copy constructor
	GameController::GameController(const GameController& other)
		: _viewController { other._viewController }
		, _game { other._game }
	{
		//_viewController = new Controller::ViewController(*other._viewController);
		//_game = new Model::Game(*other._game);
	}

	// Copy assignment operator
	GameController& GameController::operator=(const GameController& other)
	{
		if (this != &other)
		{
			if(_viewController)
				delete _viewController;
			if(_game)
				delete _game;

			GameController copy{ other };

			std::swap(*this, copy);
			
		}
		return *this;
	}


	// Move constructor
	GameController::GameController(GameController&& other)
		: _viewController { other._viewController }
		, _game { other._game }
	{
		other._viewController = nullptr;
		other._game = nullptr;
	}

	// Move assignment operator
	GameController& GameController::operator=(GameController&& other)
	{
		if (this != &other)
		{
			if(_viewController)
				delete _viewController;
			if(_game)
				delete _game;

			std::swap(_viewController, other._viewController);
			std::swap(_game, other._game);
			
			other._viewController = nullptr;
			other._game = nullptr;
		}
		return *this;
	}

} }