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
	public:
		GameController();
		GameController(const GameController& other);
		GameController & operator=(const GameController & other);
		GameController & operator=(GameController && other);
		GameController(GameController&& other);
		virtual ~GameController();

		void Start();
		const bool Update();
		void DoAction();
	};

} }