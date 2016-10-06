#pragma once

#include "Controller\GameController.h"


namespace RogueLike {
	class RogueLike {
	private:
		Controller::GameController* _gameController;
	public:
	
	private:
	public:
		RogueLike();
		RogueLike(const RogueLike& other);
		RogueLike & operator=(const RogueLike & other);
		RogueLike & operator=(RogueLike && other);
		RogueLike(RogueLike&& other);
		~RogueLike();
	};
}