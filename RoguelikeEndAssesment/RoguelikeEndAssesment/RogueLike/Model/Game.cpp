#include "Game.h"

namespace RogueLike { namespace Model {

	Game::Game()
	{
		_isGameOver = false;
		_hasDefeatedBoss = false;
		_isInCombat = false;
		_hasThreat = false;
	}
	Game::~Game()
	{
		if(_player)
			delete _player;
		if(_levelManager)
			delete _levelManager;

		if (!_enemies.empty())
		{
			for (unsigned int i = 0; i < _enemies.size(); i++)
				delete _enemies[i];
			_enemies.clear();
		}
		if (!_items.empty())
		{
			for (unsigned int i = 0; i < _items.size(); i++)
				delete _items[i];
			_items.clear();
		}
	}

	void Game::Start(uint width, uint height, uint max_levels, std::string name)
	{
		_levelManager = new LevelManager(width, height, max_levels);
		_levelManager->Start();
		_player = new Player(name, _levelManager->GetCurrentLevel()->GetStartPoint()->GetX(), _levelManager->GetCurrentLevel()->GetStartPoint()->GetY());
		this->GetCurrentPlayerRoom()->Discover();
		this->LoadEnemiesFile();
		this->LoadItemsFile();
	}

	void Game::Load(LevelManager& levelmanager, Player& player)
	{
		if (_levelManager)
			delete _levelManager;
		if (_player)
			delete _player;

		_levelManager = &levelmanager;
		_player = &player;

		_isGameOver = false;
		_hasDefeatedBoss = false;
		_isInCombat = false;
		//_hasThreat = false; // TODO: Check if _hasThreat

		this->LoadEnemiesFile();
		this->LoadItemsFile();
	}
	const bool Game::Update()
	{
		if (this->_hasDefeatedBoss) {
			this->_isGameOver = true;
		}
		return this->_isGameOver;
	}

	const std::vector<std::string> Game::GetAvailableActions() 
	{
		std::vector<std::string> options;
		if (_isInCombat) {
			options = *Globals::COMBAT_OPTIONS;
		}
		else {
			options = *Globals::ROOM_OPTIONS;
			if (!this->_hasThreat) {
				options[0] = "";
				options[1] = "";
			}
			if (this->_hasThreat)
			{
				if (!Globals::DEBUG) {
					options[3] = "";
					options[6] = "";
					options[7] = "";
					options[8] = "";
				}
			}
			if (dynamic_cast<Room::StairsRoom*> (this->GetCurrentPlayerRoom()) == nullptr) {
				options[8] = "";
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
		unsigned int amount_enemies = this->GetCurrentPlayerRoom()->GetAmountOfEnemiesAlive();
		if (amount_enemies > 0) {
			this->_hasThreat = true;
			std::string noOfEnemies = std::to_string(amount_enemies);
			if (this->_isInCombat) {
				beschrijving.append("Je bent in gevecht met " + noOfEnemies + " " + this->GetCurrentPlayerRoom()->GetEnemy()->Name + ".");
			} else {
				std::string name = (amount_enemies > 1) ? this->GetCurrentPlayerRoom()->GetEnemy()->Plural : this->GetCurrentPlayerRoom()->GetEnemy()->Name;
				std::string sentence = (amount_enemies > 1) ? "Er kijken" : "Er kijkt";
				beschrijving.append(sentence + " " + std::to_string(amount_enemies) + " " + name + " je aan.");
			}
		}
		else {
			this->_hasThreat = false;
			beschrijving.append("Er zijn geen vijanden in deze kamer");
		}
		returnValue.push_back(beschrijving);

		beschrijving = "Item:\n";
		if (this->GetCurrentPlayerRoom()->GetItem() != nullptr) {
			beschrijving.append("Er ligt een " + this->GetCurrentPlayerRoom()->GetItem()->Name + " in de kamer");
		}
		else {
			beschrijving.append("Er liggen geen bruikbare spullen in deze kamer");
		}
		returnValue.push_back(beschrijving);

		return returnValue;
	}
	const std::string Game::GetCombatInfo()
	{
		std::string returnString = "Je bent in gevecht met:";
		std::vector<Enemy*> ev = this->GetCurrentPlayerRoom()->GetEnemies();
		for (unsigned int i = 0; i < ev.size(); i++)
		{
			returnString.append("\n" + ev[i]->Name + " " + std::to_string((i + 1)) + ": " + std::to_string(ev[i]->Lifepoints) + "/" + std::to_string(ev[i]->MaxLifePoints));
		}
		returnString.append("\n\nJe levenpunten zijn " + std::to_string(this->_player->GetHp()) + "/" + std::to_string(this->_player->GetMaxHp()));
		return returnString;
	}

	const std::string Game::PlayerCombatRound()
	{
		std::string returnString = "Jij valt aan:\n";
		unsigned int dmg = this->_player->Attack();
		Enemy* enemy = this->GetCurrentPlayerRoom()->GetEnemy();
		
		if (Globals::DEBUG) {
			this->_player->Heal(this->_player->GetMaxHp());
			enemy->Damage(9001);
			returnString.append("Je aanwezigheid alleen al laat de vijand tot as vergaan.\n");
		}
		else if (dmg > 0 && enemy->Damage(dmg)) {
			returnString.append("Je doet " + std::to_string(dmg) + " schade tegen " + enemy->Name + ".\n");
		}
		else {
			returnString.append("Je slaat volslagen mis en doet geen schade aan de vijand.\n");
		}

		return returnString;
	}
	const std::string Game::EnemyCombatRound()
	{
		std::string returnString = "\nDe vijand valt je aan:";
		std::vector<Enemy*> enemies = this->GetCurrentPlayerRoom()->GetEnemies();

		for each (Enemy* foe in enemies)
		{
			if (foe->IsDead() != true) {
				unsigned int dmg = foe->Attack();
				if (dmg > 0 && this->_player->Damage(dmg)) {
					returnString.append("\nVijand " + foe->Name + " doet " + std::to_string(dmg) + " schade tegen jou.");
				}
				else {
					returnString.append("\nVijand " + foe->Name + " mist je op een haar na en doet geen schade tegen jou.");
				}
			}
			else {
				returnString.append("\nVijand " + foe->Name + " is dood.");
			}
		}

		return returnString.append("\n");
	}
	const std::string Game::CheckCombatOver()
	{
		if (this->_player->isDead()) {
			this->_isInCombat = false;
			this->_isGameOver = true;
			return "\nJe bent gestorven. De geest van " + this->_player->GetName() + " zal voor altijd door de kerker dwalen...";
		}
		else if (this->GetCurrentPlayerRoom()->GetEnemy() == nullptr) {
			this->_isInCombat = false;
			std::string sentence;
			if (dynamic_cast<Room::BossRoom*> (this->GetCurrentPlayerRoom()) != nullptr) {
				sentence = "\nGefeliciteerd! Je hebt de eindbaas van de kerker verslagen! Je hebt het spel gewonnen!";
				this->_hasDefeatedBoss = true;
			}
			else {
				const unsigned int amount = this->GetCurrentPlayerRoom()->GetAmountOfEnemies();
				sentence = (amount > 1) ? "\nJe hebt de vijanden verslagen!" : "\nJe hebt de vijand verslagen!";
				bool leveledUp = this->XpPlayerUp(this->_player, this->GetCurrentPlayerRoom()->GetEnemies());
				if (leveledUp) {
					sentence.append("\nJe hebt genoeg ervaringspunten gekregen om level omhoog te gaan! Je bent nu level " + std::to_string(this->_player->GetLvl()));
				}
			}
			return sentence;
		}
		return "";
	}
	const bool Game::XpPlayerUp(Player* player, std::vector<Enemy*> enemies)
	{
		int lvlDiff = enemies[0]->Level - player->GetLvl();
		int XpGain = 0;
		for each (Enemy* foe in enemies)
		{
			if (foe->Level + lvlDiff > 0) {
				XpGain += foe->Level + lvlDiff;
			}
		}
		return player->EarnXP(XpGain);
	}

	const bool Game::MovePlayer(int dir)
	{
		Room::Room* r = ((Room::Room*)this->GetCurrentPlayerRoom());
		if (r->GetAdjacentRooms()[dir] == nullptr) {
			return false;
		}
		this->GetCurrentPlayerRoom()->DeleteEnemies(); // Delete enemies before moving.

		int x = ((dir == 1 || dir == 3) ? ((dir == 1) ? 1 : -1) : 0);
		int y = ((dir == 0 || dir == 2) ? ((dir == 2) ? 1 : -1) : 0);

		this->_player->SetNewPlayerLocation(x, y);
		// Chance to spawn item in the room.
		if (!this->GetCurrentPlayerRoom()->IsDiscovered() || Globals::DEBUG) {
			this->GetCurrentPlayerRoom()->ChanceSpawnRandomItem(_items, _levelManager->GetLevel(), 10);
		}
		this->GetCurrentPlayerRoom()->Discover();

		// Chance to spawn enemies in the room.
		if (dynamic_cast<Room::BossRoom*> (this->GetCurrentPlayerRoom()) != NULL)
			((Room::BossRoom*)this->GetCurrentPlayerRoom())->ChanceSpawnRandomEnemies(_enemies, _levelManager->GetLevel(), 0);
		else
			((Room::Room*)this->GetCurrentPlayerRoom())->ChanceSpawnRandomEnemies(_enemies, _levelManager->GetLevel(), 4);

		return true;
	}
	const std::string Game::FleePlayer()
	{
		Room::Room* currRoom = ((Room::Room*)this->GetCurrentPlayerRoom());
		this->_isInCombat = false;
		bool success = false;
		while (!success) {
			int r = Random::GetRandom(0, 4);
			success = this->MovePlayer(r);
		}
		return "\nJe vlucht een willekeurige richting in.";
	}
	const std::string Game::UseStairs()
	{
		std::string returnString;
		if (dynamic_cast<Room::StairsRoom*> (this->GetCurrentPlayerRoom()) != nullptr) {
			Room::StairsRoom* sr = dynamic_cast<Room::StairsRoom*> (this->GetCurrentPlayerRoom());
			if (sr->IsDirectionDown()) {
				this->_levelManager->NextLevel(false);
				this->_player->TeleportPlayerLocation(this->_levelManager->GetCurrentLevel()->GetStartPoint()->GetX(), this->_levelManager->GetCurrentLevel()->GetStartPoint()->GetY());
				this->GetCurrentPlayerRoom()->Discover();
				returnString = "\nJe neemt de trap verder de donkere diepte in, met elke stap die je zet voelt het alsof de lucht je verder verstikt.";
			}
			else {
				this->_levelManager->NextLevel(true);
				this->_player->TeleportPlayerLocation(this->_levelManager->GetCurrentLevel()->GetEndPoint()->GetX(), this->_levelManager->GetCurrentLevel()->GetEndPoint()->GetY());
				returnString = "\nJe neemt de trap omhoog waar de lucht minder zwaar op je drukt.";
			}
			returnString.append("\nJe bent nu op niveau " + std::to_string(this->_levelManager->GetLevel()) + ".");
		}
		return returnString;
	}

	const std::string Game::RestPlayer()
	{
		this->_player->Heal(25);
		std::string returnString = "\nJe bent uitgerust en hebt 25 levenpunten gekregen.";
		this->GetCurrentPlayerRoom()->ChanceSpawnRandomEnemies(_enemies, this->_levelManager->GetLevel(), 7);
		if (this->GetCurrentPlayerRoom()->GetAmountOfEnemies() > 0) {
			returnString.append(" In de tijd dat je hebt uitgerust zijn er monsters verschenen.");
		}
		return returnString;
	}

	const std::string Game::LookAtPlayerInventory()
	{
		return this->_player->GetInventory();
	}
	const int Game::GetPlayerItemAmount() 
	{ 
		return this->_player->GetItems().size();
	}
	const std::string Game::UseInventory(int choice) {
		std::vector<Item*> items = this->_player->GetItems();
		if (choice < 1 || choice > (int)items.size()) {
			return "";
		}
		return this->_player->UseItem(--choice);
	}
	const std::string Game::TakeItem()
	{
		Item* item = this->GetCurrentPlayerRoom()->GetItem();
		if (item == nullptr)
		{
			return "Je doorzoekt de kamer maar je vind geen bruikbare spullen.";
		}
		if (this->_player->AddItemToInventory(*item) == true)
		{
			this->GetCurrentPlayerRoom()->RemoveItem();
			return "Je hebt het " + item->Name + " opgepakt en in je zak gestopt bij de rest van de spullen.";
		} else {
			// The item will be remove after moving the player to another room.
			return "Je merkt dat je er al teveel van hebt, dus je hebt besloten om het te laten liggen.";
		}
	}

	Room::Room* Game::GetCurrentPlayerRoom()
	{
		return ((Room::Room*)_levelManager->GetCurrentLevel()->GetLocations()[(_player->GetY() * _levelManager->GetLevelWidth()) + _player->GetX()]);
	}

	void Game::GameOver()
	{
		this->_isGameOver = true;
	}
	void Game::StartCombat()
	{
		this->_isInCombat = true;
	}
	void Game::EndCombat()
	{
		this->_isInCombat = false;
	}

	const char* const Game::GetMap()
	{
		return this->_levelManager->GetMap(this->_player->GetX(), this->_player->GetY());
	}

	void Game::LoadEnemiesFile()
	{
		try
		{
			Utils::File f("./Assets/monsters.txt");
			std::string s = f.Read();


			size_t pos = 0;
			std::string delimiter = "]";
			std::vector<std::string> tokens;
			std::string token = "";


			// Remove newlines
			while ((pos = s.find("\r\n")) != std::string::npos) { s.erase(pos, 2); }


			// split monsters
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());

				token.erase(0, 1); // Remove [
				tokens.push_back(token);
			}

			for each(std::string monster in tokens)
			{
				Enemy* enemy = new Enemy();
				unsigned int index = 0;
				std::string percentage = "";
				std::string amount_attacks = "";
				std::string min_damage = "";
				std::string max_damage = "";
				while (!monster.empty())
				{
					pos = (monster.find_first_of(';', 1) != std::string::npos) ? monster.find_first_of(';', 1) : monster.size();
					token = monster.substr(0, pos);
					monster.erase(0, pos + 1);
					
					switch (index)
					{
					case 0: // Naam
						enemy->Name = token;
						break;
					case 1: // Naam in meervoud
						enemy->Plural = token;
						break;
					case 2: // Level
						if (token == "BAAS")
						{
							enemy->Level = 0;
							enemy->Type = Enum::EnemyType::BOSS;
						}
						else {
							enemy->Level = FromString<int>(token);
							enemy->Type = Enum::EnemyType::NORMAL;
						}
						break;
					case 3: // Aanval
						percentage = token.substr(0, token.find('x'));
						amount_attacks = token.substr(token.find('x') + 1, token.size() - 1);
						enemy->Hitchance = FromString<int>(percentage);
						enemy->AmountAttacks = FromString<int>(amount_attacks);
						break;
					case 4: // Schade
						min_damage = token.substr(0, token.find('-'));
						max_damage = token.substr(token.find('-') + 1, token.size() - 1);
						enemy->MinDamage = FromString<int>(min_damage);
						enemy->MaxDamage = FromString<int>(max_damage);
						break;
					case 5: // Verdediging
						enemy->Defence = FromString<int>(token);
						break;
					case 6: // Levenspunten
						enemy->Lifepoints = FromString<int>(token);
						enemy->MaxLifePoints = enemy->Lifepoints;
						break;
					default:
						break;
					}
					index++;
				}
				this->_enemies.push_back(enemy);
			}

		}
		catch (ErrorHandling::FileNotFoundException& e) {
			std::cout << "Error during reading monsters.txt file: ";
			std::cout << e.what() << std::endl;
		}
	}
	void Game::LoadItemsFile()
	{
		try
		{
			Utils::File f("./Assets/items.txt");
			std::string s = f.Read();


			size_t pos = 0;
			std::string delimiter = "]";
			std::vector<std::string> tokens;
			std::string token = "";


			// Remove newlines
			while ((pos = s.find("\r\n")) != std::string::npos) { s.erase(pos, 2); }


			// split items
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());

				token.erase(0, 1); // Remove [
				tokens.push_back(token);
			}

			for each(std::string item in tokens)
			{
				Item* _item = new Item();
				unsigned int index = 0;
				while (!item.empty())
				{
					pos = (item.find_first_of(';', 1) != std::string::npos) ? item.find_first_of(';', 1) : item.size();
					token = item.substr(0, pos);
					item.erase(0, pos + 1);

					int ability = 0;
					switch (index)
					{
					case 0: // Naam
						_item->Name = token;
						break;
					case 1: // Naam in meervoud
						_item->Plural = token;
						break;
					case 2: // Maximaal aantal
						_item->MaxAmount = FromString<int>(token);
						break;
					case 3: // Ability
						ability = FromString<int>(token);
						if (ability >= 0 && ability < static_cast<int>(Enum::ItemType::COUNT))
							_item->Ability = (Enum::ItemType)(ability);
						else
							_item->Ability = Enum::ItemType::XP;
						break;
					case 4: // Effect
						_item->Effect = FromString<int>(token);
						break;
					case 5: // Beschrijving
						_item->Description = token;
						break;
					default:
						break;
					}
					index++;
				}
				this->_items.push_back(_item);
			}

		}
		catch (ErrorHandling::FileNotFoundException& e) {
			std::cout << "Error during reading items.txt file: ";
			std::cout << e.what() << std::endl;
		}
	}

	const std::string Game::GetPlayerVitalsAsString() const
	{
		return this->_player->GetVitalsAsString();
	}
	const std::string Game::GetLevelsAsString() const
	{
		return this->_levelManager->GetLevelsAsString();
	}
	const int Game::GetPlayerCurrentLevel() const
	{
		return this->_levelManager->GetLevel();
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