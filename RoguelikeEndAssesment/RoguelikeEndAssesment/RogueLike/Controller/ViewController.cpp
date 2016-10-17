
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


	// Copy constructor
	ViewController::ViewController(const ViewController& other)
	{
		_inputView = new View::InputView(*other._inputView);
		_outputView = new View::OutputView(*other._outputView);
	}

	// Copy assignment operator
	ViewController& ViewController::operator=(const ViewController& other)
	{
		if (this != &other)
		{
			delete _inputView;
			delete _outputView;

			_inputView = new View::InputView();
			_outputView = new View::OutputView();

			_inputView = other._inputView;
			_outputView = other._outputView;
		}
		return *this;
	}


	// Move constructor
	ViewController::ViewController(ViewController&& other)
	{
		_inputView = other._inputView;
		_outputView = other._outputView;

		other._inputView = nullptr;
		other._outputView = nullptr;
	}

	// Move assignment operator
	ViewController& ViewController::operator=(ViewController&& other)
	{
		if (this != &other)
		{
			delete _inputView;
			delete _outputView;

			_inputView = other._inputView;
			_outputView = other._outputView;

			other._inputView = nullptr;
			other._outputView = nullptr;
		}
		return *this;
	}

} }