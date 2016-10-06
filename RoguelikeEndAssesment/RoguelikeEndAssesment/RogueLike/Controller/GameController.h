#pragma once

#include "ViewController.h"

namespace RogueLike { namespace Controller {
	
	class GameController {
	private:
		ViewController* _viewController;
	public:

	private:
	public:
		GameController();
		GameController(const GameController& other);
		GameController & operator=(const GameController & other);
		GameController & operator=(GameController && other);
		GameController(GameController&& other);
		~GameController();
	};

} }