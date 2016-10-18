#pragma once
#include "../View/InputView.h"
#include "../View/OutputView.h"
#include "../Common.h"

namespace RogueLike { namespace Controller {

	class ViewController {
	private:
		View::InputView* _inputView;
		View::OutputView* _outputView;
	public:

	private:
	public:
		ViewController();
		~ViewController();
		ViewController(const ViewController& other);
		ViewController & operator=(const ViewController& other);
		ViewController & operator=(ViewController&& other);
		ViewController(ViewController&& other);

		void ShowWelcomeScreen();
		void ShowMap(char* map, unsigned int width, unsigned int height);
		char GetStartScreenInput();
		uint AskInt(std::string message, unsigned int maxInt);
		void Say(const std::string& message);

		void PressAnyKeyToContinue();
	};

} }