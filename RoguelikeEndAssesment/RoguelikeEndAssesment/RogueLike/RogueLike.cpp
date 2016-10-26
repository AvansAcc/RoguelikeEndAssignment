#include "RogueLike.h"

namespace RogueLike {

	RogueLike::RogueLike()
	{
		this->_running = false;
		_gameController = new Controller::GameController();
	}
	RogueLike::~RogueLike()
	{
		delete _gameController;
		
		delete Globals::COMBAT_OPTIONS;
		delete Globals::ROOM_OPTIONS;
	}
	
	void RogueLike::Start()
	{
		this->_running = true;
		this->_gameController->Start();
		this->Update();
	}

	void RogueLike::Update()
	{
		while (this->_running)
		{
			_running = this->_gameController->Update();
		}
		this->Quit();
	}

	void RogueLike::Quit()
	{
		this->_running = false;
	}

	// Copy constructor
	RogueLike::RogueLike(const RogueLike& other)
		: _gameController { other._gameController }
	{

	}
	// Copy assignment operator
	RogueLike& RogueLike::operator=(const RogueLike& other)
	{
		if (this != &other)
		{
			if(this->_gameController)
				delete this->_gameController;

			RogueLike copy { other };

			std::swap(*this, copy);
		}
		return *this;
	}
	// Move constructor
	RogueLike::RogueLike(RogueLike&& other)
		: _gameController { other._gameController }
	{
		other._gameController = nullptr;
	}
	// Move assignment operator
	RogueLike& RogueLike::operator=(RogueLike&& other)
	{
		if (this != &other)
		{
			if(_gameController)
				delete _gameController;

			std::swap(_gameController, other._gameController);
			
			other._gameController = nullptr;
		}
		return *this;
	}
}