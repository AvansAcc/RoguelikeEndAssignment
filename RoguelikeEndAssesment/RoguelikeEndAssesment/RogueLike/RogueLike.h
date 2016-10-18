#pragma once

#include "Controller\GameController.h"


namespace RogueLike {
	class RogueLike {
	private:
		Controller::GameController* _gameController;
		bool _running;
	public:
	
	private:
		void Update();
		void Quit();
	public:
		void Start();

		RogueLike();
		RogueLike(const RogueLike& other);
		RogueLike & operator=(const RogueLike & other);
		RogueLike & operator=(RogueLike && other);
		RogueLike(RogueLike&& other);
		~RogueLike();
	};
}