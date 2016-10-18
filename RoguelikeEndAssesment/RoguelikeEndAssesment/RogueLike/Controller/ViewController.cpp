#include "ViewController.h"

namespace RogueLike { namespace Controller {

	ViewController::ViewController()
	{
		_inputView = new View::InputView();
		_outputView = new View::OutputView();
	}

	ViewController::~ViewController()
	{
		delete _inputView;
		delete _outputView;
	}



	void ViewController::ShowWelcomeScreen()
	{
		_outputView->ShowWelcomScreen();
	}

	void ViewController::ShowMap(char* map, unsigned int width, unsigned int height)
	{
		this->_outputView->ShowMap(map, width, height);
	}

	char ViewController::GetStartScreenInput()
	{
		// TODO: Check the expected input and return it. Else: ask again.
		this->_inputView->AskWord();
		return '.';
	}

	void ViewController::PressAnyKeyToContinue()
	{
		this->_inputView->AskLetter();
	}

	void ViewController::Say(const std::string& message)
	{
		this->_outputView->Say(message);
	}


	uint ViewController::AskInt(std::string message, unsigned int maxInt)
	{
		uint result = 0;
		while (result < 1)
		{
			result = this->_inputView->AskInt(message);
			if (result > maxInt)
			{
				result = 0;
			}
		}
		return result;
	}



	// Copy constructor
	ViewController::ViewController(const ViewController& other)
		: _inputView { other._inputView }
		, _outputView { other._outputView }
	{
		//_inputView = new View::InputView(*other._inputView);
		//_outputView = new View::OutputView(*other._outputView);
	}

	// Copy assignment operator
	ViewController& ViewController::operator=(const ViewController& other)
	{
		if (this != &other)
		{
			if(_inputView)
				delete _inputView;
			if(_outputView)
				delete _outputView;

			ViewController copy{ other };

			std::swap(*this, copy);
		}
		return *this;
	}

	// Move constructor
	ViewController::ViewController(ViewController&& other)
		: _inputView { other._inputView }
		, _outputView { other._outputView }
	{
		other._inputView = nullptr;
		other._outputView = nullptr;
	}

	// Move assignment operator
	ViewController& ViewController::operator=(ViewController&& other)
	{
		if (this != &other)
		{
			if(_inputView)
				delete _inputView;
			if(_outputView)
				delete _outputView;

			std::swap(_inputView, other._inputView);
			std::swap(_outputView, other._outputView);

			other._inputView = nullptr;
			other._outputView = nullptr;
		}
		return *this;
	}

} }