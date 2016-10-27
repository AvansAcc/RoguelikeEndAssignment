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
		uint width = this->_viewController->AskInt("Hoe breedt zal de kerker worden? (min 2, max 25)", 2, 25);
		uint height = this->_viewController->AskInt("Hoe lang zal de kerker worden? (min 2, max 25)", 2, 25);
		uint max_levels = this->_viewController->AskInt("Hoe diep zal de kerken zijn? (max 10)", 10);
		std::string name = this->_viewController->AskWord("Ten slotte, hoe heet onze held?");
		this->_viewController->Say("Bedankt voor je geduld... Laat het avontuur maar beginnen!\n\n");

		this->_game->Start(width, height, max_levels, name);
	}

	void GameController::LoadGame()
	{
		// TODO load game
	}

	const bool GameController::Update()
	{
		bool returnValue = (_game != nullptr) ? !_game->Update() : false;
		if (returnValue) {
			this->DoAction();
		}
		else {
			this->_viewController->ShowCloseScreen();
		}
		return returnValue;
	}

	void GameController::DoAction()
	{
		std::vector<std::string> gameInfo = this->_game->GetGameInfo();
		this->_viewController->ShowGame(gameInfo);

		std::vector<std::string> options = this->_game->GetAvailableActions();
		int choice = this->_viewController->ShowOptions(options);
		bool isAllowed = true;

		switch (choice)
		{
			case 1: // Vechten
			{
				if (this->_game->HasThreat()) {
					this->StartCombatRound();
				}
				break;
			}
			case 2: // Vluchten
			{
				if (this->_game->HasThreat()) {
					this->_game->EndCombat();
					this->_viewController->Say(this->_game->FleePlayer());
					this->_viewController->PressAnyKeyToContinue();
				}
				break;
			}
			case 3: // Spullen bekijken
			{
				this->LookAtInventory();
				break;
			}
			case 4: // Uitrusten
			{
				if (!this->_game->IsInCombat() || !this->_game->HasThreat()) {
					this->_viewController->Say(this->_game->RestPlayer());
					this->_viewController->PressAnyKeyToContinue();
				}
				break;
			}
			case 5: // Eigenschappen speler zien
			{
				if (!this->_game->IsInCombat()) {
					this->_viewController->Say(this->_game->GetPlayerVitals());
					this->_viewController->PressAnyKeyToContinue();
				}
				break;
			}
			case 6: // Kaart bekijken
			{
				if (!this->_game->IsInCombat()) {
					const char* const map = this->_game->GetMap();
					this->_viewController->ShowMap(map, this->_game->GetLevelWidth(), this->_game->GetLevelHeight());
					delete[] map;
				}
				break;
			}
			case 7: // Item oppakken
			{
				if (!this->_game->IsInCombat() || !this->_game->HasThreat()) {
					this->_game->TakeItem();
				}
				break;
			}
			case 8: // Verplaatsen
			{
				if (!this->_game->IsInCombat() && (!this->_game->HasThreat() || Globals::DEBUG)) {
					this->HandleDirChoice();
				}
				break;
			}
			case 9: // Trap gebruiken
			{
				if (!this->_game->IsInCombat() && !this->_game->HasThreat()) {
					this->UseStairs();
				}
				break;
			}
			case 10: // Exit
			{
				if (!this->_game->IsInCombat()) {
					this->Save();
					this->_game->GameOver();
				}
				break;
			}
			default:
				break;
		}
	}

	void GameController::HandleDirChoice()
	{	
		bool isvalid = false;
		bool wrongAnswer = true;
		while (!isvalid)
		{
			if (!wrongAnswer) {
				this->_viewController->Say("\nDat is helaas geen richting waar je heen kunt");
			}
			std::string dir = this->_viewController->AskWord("\nWelke richting wil je op? (noord, oost, zuid, west) (typ \"b\" als je terug wilt)");
			if (dir == "noord") {
				isvalid = this->_game->MovePlayer(0);
			}
			else if (dir == "oost") {
				isvalid = this->_game->MovePlayer(1);
			}
			else if (dir == "zuid") {
				isvalid = this->_game->MovePlayer(2);
			}
			else if (dir == "west") {
				isvalid = this->_game->MovePlayer(3);
			}
			else if (dir == "b") {
				isvalid = true;
			}
			wrongAnswer = isvalid;
		}
	}

	void GameController::LookAtInventory() 
	{
		this->_viewController->Say(this->_game->LookAtPlayerInventory());
		this->_viewController->PressAnyKeyToContinue();
		// TODO interface voor items gebruiken bouwen

	}

	void GameController::UseStairs()
	{
		std::string s = this->_game->UseStairs();
		this->_viewController->Say(s);
		if (!s.empty()) {
			this->_viewController->PressAnyKeyToContinue();
		}
	}

	void GameController::StartCombatRound()
	{
		this->_game->StartCombat();
		while (this->_game->IsInCombat()) {
			this->_viewController->ClearScreen();
			this->_viewController->Say(this->_game->GetCombatInfo());

			std::vector<std::string> options = this->_game->GetAvailableActions();
			int choice = this->_viewController->ShowOptions(options);

			switch (choice)
			{
				case 1: // Vechten
				{
					this->_viewController->Say(this->_game->PlayerCombatRound());
					this->_viewController->Say(this->_game->EnemyCombatRound());
					break;
				}
				case 2: // Vluchten
				{
					this->_game->EndCombat();
					this->_viewController->Say(this->_game->FleePlayer());
					this->_viewController->PressAnyKeyToContinue();
					break;
				}
				case 3: // Spullen bekijken
				{
					this->LookAtInventory();
					break;
				}
			}
			this->_viewController->Say(this->_game->CheckCombatOver());
			this->_viewController->PressAnyKeyToContinue();
		}
	}

	void GameController::Save()
	{
		//TODO ask for save and save accordingly
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