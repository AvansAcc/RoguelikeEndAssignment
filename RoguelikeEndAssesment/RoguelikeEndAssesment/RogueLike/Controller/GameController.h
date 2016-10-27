#pragma once

#include "ViewController.h"
#include "../Model/Game.h"

namespace RogueLike { namespace Controller {
	
	class GameController {
	private:
		ViewController* _viewController;
		Model::Game* _game;
	public:

	private:
		void StartNewGame();
		void LoadGame();
		void HandleDirChoice();
		void LookAtInventory();
		void UseStairs();
		void StartCombatRound();
		void Save();
	public:
		GameController();
		virtual ~GameController();
		GameController(const GameController& other);
		GameController & operator=(const GameController & other);
		GameController & operator=(GameController && other);
		GameController(GameController&& other);

		void Start();
		const bool Update();
		void DoAction();
	};

} }