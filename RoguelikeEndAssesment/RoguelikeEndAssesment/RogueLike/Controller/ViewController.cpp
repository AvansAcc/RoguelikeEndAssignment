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

	void ViewController::ClearScreen() 
	{
		system("cls");
	}

	void ViewController::ShowWelcomeScreen()
	{
		this->ClearScreen();
		_outputView->ShowWelcomScreen();
		this->PressAnyKeyToContinue();
	}

	const int ViewController::ShowMenuScreen()
	{
		this->ClearScreen();
		this->Say("Kerkers en draken\n\n");
		std::vector<std::string> menuItems{ "Nieuw spel", "Spel laden", "Spel opslaan", "Credits", "Afsluiten" };
		_outputView->ShowMenu(menuItems);
		return this->AskInt("\nMaak uw keuze uit de menu items (geef het nummer mee)", (unsigned int)menuItems.size());
	}

	void ViewController::ShowCreditScreen()
	{
		this->ClearScreen();
		this->Say("Dit project is gemaakt voor de C++1 eindopdracht op Avans hogeschool\n\n");
		this->Say("Gemaakt door:\nRick Smeets\nMartin van der Geest\n");
		this->PressAnyKeyToContinue();
	}

	void ViewController::ShowCloseScreen()
	{
		_outputView->ShowQuit();
		this->PressAnyKeyToContinue();
	}

	const int ViewController::ShowOptions(std::vector<std::string> options)
	{
		this->_outputView->ShowOptions(options);
		return this->AskInt("\n", (unsigned int)options.size());
	}

	void ViewController::ShowMap(const char* const map, unsigned int width, unsigned int height)
	{
		this->ClearScreen();
		this->_outputView->ShowMap(map, width, height);
		this->PressAnyKeyToContinue();
	}

	void ViewController::ShowGame(std::vector<std::string> gameInfo)
	{
		this->ClearScreen();

		this->_outputView->ShowGame(gameInfo);
	}

	void ViewController::PressAnyKeyToContinue()
	{
		this->Say("\nDruk op enter om door te gaan...");
		this->_inputView->AskLetter();
	}

	void ViewController::Say(const std::string& message)
	{
		this->_outputView->Say(message);
	}

	std::string ViewController::AskWord(std::string message)
	{
		std::string result = "";
		while (result.empty())
		{
			result = this->_inputView->AskWord(message);
		}
		return result;
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

	uint ViewController::AskInt(std::string message, unsigned int minInt, unsigned int maxInt)
	{
		uint result = 0;
		while (result < 1)
		{
			result = this->_inputView->AskInt(message);
			if (result > maxInt || result < minInt)
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