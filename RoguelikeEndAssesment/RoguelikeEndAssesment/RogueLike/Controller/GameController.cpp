#include "GameController.h"

namespace RogueLike { namespace Controller {

	GameController::GameController()
	{
		_viewController = new ViewController();
		_running = false;
	}

	GameController::~GameController()
	{
		delete _viewController;
		if(_game)
			delete _game;
	}

	void GameController::Start()
	{
		_running = true;
		this->_viewController->ShowWelcomeScreen();
		
		this->ShowMenu();
	}

	void GameController::StartNewGame()
	{
		if (_game) delete _game;
		_game = new Model::Game();
		this->_viewController->ClearScreen();
		uint width = this->_viewController->AskInt("Hoe breedt zal de kerker worden? (min 2, max 25)", 2, 25);
		uint height = this->_viewController->AskInt("Hoe lang zal de kerker worden? (min 2, max 25)", 2, 25);
		uint max_levels = this->_viewController->AskInt("Hoe diep zal de kerken zijn? (min 1, max 10)", 10);
		std::string name = this->_viewController->AskWord("Ten slotte, hoe heet onze held?");
		this->_viewController->Say("Bedankt voor je geduld... Laat het avontuur maar beginnen!\n\n");

		this->_game->Start(width, height, max_levels, name);
	}

	const bool GameController::Update()
	{
		_running = (_game != nullptr) ? !_game->Update() : false;
		
		if (_running)
			this->DoAction();
		else
			this->ShowMenu();
	
		if (!_running) {
			this->_viewController->ShowCreditScreen();
			this->_viewController->ShowCloseScreen();
		}

		return _running;
	}
	void GameController::ShowMenu()
	{
		bool menuBool = true;
		while (menuBool)
		{
			int menuChoice = this->_viewController->ShowMenuScreen();

			if (menuChoice == 1) {
				menuBool = false;
				this->StartNewGame();
				_running = true;
			}
			else if (menuChoice == 2) {
				menuBool = false;
				this->LoadGame();
				_running = true;
			}
			else if (menuChoice == 3) {
				menuBool = false;
				this->Save();
				_running = true;
			}
			else if (menuChoice == 4) {
				this->_viewController->ShowCreditScreen();
				_running = true;
			}
			else if (menuChoice == 5) {
				menuBool = false;
				_running = false;
			}
		}
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
				if ((!this->_game->IsInCombat() && !this->_game->HasThreat()) || Globals::DEBUG) {
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
				if ((!this->_game->IsInCombat() && !this->_game->HasThreat()) || Globals::DEBUG) {
					this->_viewController->Say(this->_game->TakeItem());
					this->_viewController->PressAnyKeyToContinue();
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
			case 11:
			{
				if (!this->_game->IsInCombat()) {
					this->_viewController->Say(this->_game->BreadthFirstSearch());
					this->_viewController->PressAnyKeyToContinue();
				}
				break;
			}
			case 12:
			{
				if (!this->_game->IsInCombat()) {
					this->_viewController->Say(this->_game->ShortestPathV2());
					this->_viewController->PressAnyKeyToContinue();
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
		if (this->_game->GetPlayerItemAmount() > 0)
		{
			bool isvalid = false;
			bool useItem = false;
			while (!isvalid)
			{
				std::string answer = this->_viewController->AskWord("\nWil je iets gebruiken? (Y voor ja, N voor nee)");
				if (answer == "Y" || answer == "y") {
					isvalid = true;
					useItem = true;
				}
				else if (answer == "N" || answer == "n") {
					isvalid = true;
				}
			}

			isvalid = !useItem;
			while (!isvalid)
			{
				int choice = this->_viewController->AskInt("\nWelk item wil je gebruiken? (kies het bijbehorende getal)", 5);

				std::string answer = this->_game->UseInventory(choice);
				if (!answer.empty()) {
					this->_viewController->Say(answer);
					isvalid = true;
				}
			}
		}
		this->_viewController->PressAnyKeyToContinue();
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
					this->_viewController->Say(this->_game->CheckCombatOver());
					this->_viewController->PressAnyKeyToContinue();
					break;
				}
				case 2: // Vluchten
				{
					this->_viewController->Say(this->_game->FleePlayer());
					this->_viewController->PressAnyKeyToContinue();
					break;
				}
				case 3: // Spullen bekijken
				{
					this->LookAtInventory();
					this->_viewController->Say(this->_game->EnemyCombatRound());
					this->_viewController->Say(this->_game->CheckCombatOver());
					this->_viewController->PressAnyKeyToContinue();
					break;
				}
			}
		}
	}

	void GameController::Save()
	{
		if (this->_game == nullptr) {
			this->_viewController->Say("Geen geldige game gevonden om op te slaan.\n");
			this->_viewController->PressAnyKeyToContinue();
			return;
		}
		Utils::File f("./Assets/SaveFile.txt");
		std::string savestring = "";
		
		// The Map
		savestring.append("{");
		savestring.append(std::to_string(this->_game->GetLevelWidth())).append(";");	// Width of Map
		savestring.append(std::to_string(this->_game->GetLevelHeight())).append(";");	// Height of Map
		savestring.append(std::to_string(this->_game->GetMaxDepth())).append(";");		// Depth of Map
		savestring.append(std::to_string(this->_game->GetPlayerCurrentLevel()));		// Player's Depth
		savestring.append("}");

		// Player
		savestring.append(this->_game->GetPlayerVitalsAsString());

		// Level with rooms (with items & enemies)
		savestring.append(this->_game->GetLevelsAsString());

		try
		{
			if (f.Write(savestring, true))
				this->_viewController->Say("Alles is succesvol opgeslagen!\n");
			else
				this->_viewController->Say("Er ging iets fout tijdens het opslaan van de game status.\n");
		}
		catch (ErrorHandling::FileNotFoundException& e)
		{
			std::string error_msg = "Er ging iets fout tijdens het opslaan: ";
			error_msg.append(e.what()).append("\n");
			this->_viewController->Say(error_msg);
		}
		this->_viewController->PressAnyKeyToContinue();
	}
	void GameController::LoadGame()
	{
		Utils::File f("./Assets/SaveFile.txt");
		
		std::vector<Model::Level*> levels;
		std::vector<Model::Room::IRoom*> rooms;
		std::vector<Model::Item*> player_items;
		Model::Item* item = nullptr;
		Model::Player* player = nullptr;
		Model::LevelManager* levelmanager = nullptr;
		Model::Game* game = nullptr;
		try
		{
			std::string loadedfile = f.Read();

			size_t pos = 0;
			std::string token = "";
			std::vector<std::string> tokens;
			int index = 0;

			// Remove newlines
			while ((pos = loadedfile.find("\r\n")) != std::string::npos) { loadedfile.erase(pos, 2); }

			// Split main parts
			while ((pos = loadedfile.find('}')) != std::string::npos) {
				token = loadedfile.substr(0, pos);
				loadedfile.erase(0, pos + 1);

				token.erase(0, 1); // Remove {
				tokens.push_back(token);
			}

			if (tokens.size() <= 0)
				throw ErrorHandling::Exception("File is empty!");
			
			// Load Levels
			/*std::vector<Model::Level*> levels;
			std::string levelsstring = tokens.back();
			//TODO

			// Load Rooms
			std::vector<Model::Room::IRoom*> rooms;
			// TODO

			*/
			if(tokens.size() > 0)
				tokens.pop_back(); // Remove Levels from tokens

			// Load Items of Player
			player_items.clear();
			std::string playeritemsstring = (tokens.size() > 0) ? tokens.back() : "";
			std::vector<std::string> item_tokens;
			std::string itemstring = "";
			
			while ((pos = playeritemsstring.find(']')) != std::string::npos) {
				token = playeritemsstring.substr(0, pos);
				playeritemsstring.erase(0, pos + 1);
				index = 0;
				
				item = new Model::Item();
				while (!token.empty()) {
					pos = (token.find_first_of(';', 1) != std::string::npos) ? token.find_first_of(';', 1) : token.size();
					itemstring = token.substr(0, pos);
					token.erase(0, pos + 1);

					switch (index)
					{
					case 0:
						item->Name = itemstring;
						break;
					case 1:
						item->Plural = itemstring;
						break;
					case 2:
						item->Amount = FromString<unsigned int>(itemstring);
						break;
					case 3:
						item->MaxAmount = FromString<unsigned int>(itemstring);
						break;
					case 4:
						item->Ability = (Model::Enum::ItemType)(FromString<int>(itemstring));
						break;
					case 5:
						item->Effect = FromString<int>(itemstring);
						break;
					case 6:
						item->Description = itemstring;
						break;
					}
					index++;
				}
				player_items.push_back(item);

				playeritemsstring.erase(0, 1); // Remove [
				item_tokens.push_back(token);
			}
			if (tokens.size() > 0)
				tokens.pop_back(); // Remove items of player from tokens

			// Load Player
			std::string playerstring = (tokens.size() > 0) ? tokens.back() : "";
			std::string player_name = "";
			unsigned int player_x_pos = 0;
			unsigned int player_y_pos = 0;
			unsigned int player_level = 0;
			unsigned int player_attack = 0;
			unsigned int player_defence = 0;
			unsigned int player_xp = 0;
			unsigned int player_lifepoints = 0;
			index = 0;

			while (!playerstring.empty()) {
				pos = (playerstring.find_first_of(';', 1) != std::string::npos) ? playerstring.find_first_of(';', 1) : playerstring.size();
				token = playerstring.substr(0, pos);
				playerstring.erase(0, pos + 1);

				switch (index)
				{
				case 0:
					player_name = token;
					break;
				case 1:
					player_level = FromString<unsigned int>(token);
					break;
				case 2:
					player_x_pos = FromString<unsigned int>(token);
					break;
				case 3:
					player_y_pos = FromString<unsigned int>(token);
					break;
				case 4:
					player_attack = FromString<unsigned int>(token);
					break;
				case 5:
					player_defence = FromString<unsigned int>(token);
					break;
				case 6:
					player_xp = FromString<unsigned int>(token);
					break;
				case 7:
					player_lifepoints = FromString<unsigned int>(token);
					break;
				}
				index++;
			}

			player = new Model::Player(player_name, player_x_pos, player_y_pos);
			player->Load(player_level, player_attack, player_defence, player_lifepoints, player_xp, player_items);
			if (tokens.size() > 0)
				tokens.pop_back(); // Remove Player from tokens


			// Load LevelManager
			std::string levelmanagerstring = (tokens.size() > 0) ? tokens.back() : "";
			index = 0;
			unsigned int level_width = 0;		// Level Width
			unsigned int level_height = 0;		// Level Height
			unsigned int level_depth = 0;		// Max Depth
			unsigned int player_depth = 0;		// Player's current Depth
			while (!levelmanagerstring.empty()) {
				pos = (levelmanagerstring.find_first_of(';', 1) != std::string::npos) ? levelmanagerstring.find_first_of(';', 1) : levelmanagerstring.size();
				token = levelmanagerstring.substr(0, pos);
				levelmanagerstring.erase(0, pos + 1);

				switch (index)
				{
				case 0:
					level_width = FromString<unsigned int>(token);		// Level Width
					break;
				case 1:
					level_height = FromString<unsigned int>(token);		// Level Height
					break;
				case 2:
					level_depth = FromString<unsigned int>(token);		// Max Depth
					break;
				case 3:
					player_depth = FromString<unsigned int>(token);		// Player's current Depth
					break;
				}
				index++;
			}

			levelmanager = new Model::LevelManager(level_width, level_height, level_depth);
			levelmanager->Load(player_depth, levels);
			if (tokens.size() > 0)
				tokens.pop_back(); // Remove levelmanager from tokens
			
			if(levels.empty())
				player->TeleportPlayerLocation(levelmanager->GetCurrentLevel()->GetStartPoint()->GetX(), levelmanager->GetCurrentLevel()->GetStartPoint()->GetY());

			// Load Game
			game = new Model::Game();
			if (this->_game)
				delete _game;
			 this->_game = game;

			 // Start the game
			 this->_running = true;
			 this->_game->Load(*levelmanager, *player);
		}
		catch (ErrorHandling::FileNotFoundException& e)
		{
			std::string error_msg = "Er ging iets fout tijden het lezen van het bestand...";
			error_msg.append(e.what());
			this->_viewController->Say(error_msg);
			this->_viewController->PressAnyKeyToContinue();
		}
		catch (ErrorHandling::Exception& e)
		{
			if (!levels.empty())
			{
				for (unsigned int i = 0; i < levels.size(); i++)
					delete levels[i];
				levels.clear();
			}
			if (!rooms.empty())
			{
				for (unsigned int i = 0; i < rooms.size(); i++)
					delete rooms[i];
				rooms.clear();
			}
			if (!player_items.empty())
			{
				for (unsigned int i = 0; i < player_items.size(); i++)
					delete player_items[i];
				player_items.clear();
			}
			if (item)
				delete item;
			item = nullptr;
			if (player)
				delete player;
			player = nullptr;
			if (levelmanager)
				delete levelmanager;
			levelmanager = nullptr;
			if (game)
				delete game;
			game = nullptr;

			std::string error_msg = "Er ging iets fout tijden het laden van het bestand...";
			error_msg.append(e.what()).append("\n");
			this->_viewController->Say(error_msg);
			this->_viewController->PressAnyKeyToContinue();
		}
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