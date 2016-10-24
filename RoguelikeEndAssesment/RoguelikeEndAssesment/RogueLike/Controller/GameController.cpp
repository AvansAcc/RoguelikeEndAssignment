#include "GameController.h"

namespace RogueLike { namespace Controller {

	GameController::GameController()
	{
		_viewController = new ViewController();
	}

	GameController::~GameController()
	{
		delete _viewController;
		if(_game)
			delete _game;
	}

	void GameController::Start()
	{
		this->_viewController->ShowWelcomeScreen();
		
		bool menuBool = true;
		while (menuBool)
		{
			int menuChoice = this->_viewController->ShowMenuScreen();

			if (menuChoice == 1) {
				menuBool = false;
				this->StartNewGame();
			}
			else if (menuChoice == 2) {
				menuBool = false;
				this->LoadGame();
			}
			else if (menuChoice == 3) {
				this->_viewController->ShowCreditScreen();
			}
			else if (menuChoice == 4) {
				menuBool = false;
			}
		}
	}

	void GameController::StartNewGame()
	{
		_game = new Model::Game();
		this->_viewController->ClearScreen();
		uint width = this->_viewController->AskInt("Hoe breedt zal de kerker worden? (max 25)", 25);
		uint height = this->_viewController->AskInt("Hoe lang zal de kerker worden? (max 25)", 25);
		uint max_levels = this->_viewController->AskInt("Hoe diep zal de kerken zijn? (max 10)", 10);
		std::string name = this->_viewController->AskWord("Ten slotte, hoe heet onze held?");
		this->_viewController->Say("Bedankt voor je geduld... Laat het avontuur maar beginnen!\n\n");

		this->_game->Start(width, height, max_levels, name);

		/*const char* const map = this->_game->GetMap();
		this->_viewController->ShowMap(map, this->_game->GetLevelWidth(), this->_game->GetLevelHeight());
		delete[] map;
		system("PAUSE");*/
	}

	void GameController::LoadGame()
	{
		// TODO load game
	}

	const bool GameController::Update()
	{
		bool returnValue = _game->Update();
		if (!returnValue) {
			this->DoAction();
		}
		else {
			this->_viewController->ShowCloseScreen();
		}
		return this->_game->Update();
	}

	void GameController::DoAction()
	{
		std::vector<std::string> options = this->_game->GetAvailableActions();
		int choice = this->_viewController->ShowOptions(options);


	}


	// Copy constructor
	GameController::GameController(const GameController& other)
		: _viewController { other._viewController }
		, _game { other._game }
	{
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