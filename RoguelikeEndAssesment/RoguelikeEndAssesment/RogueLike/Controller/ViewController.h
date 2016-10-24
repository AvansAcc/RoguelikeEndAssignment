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
		virtual ~ViewController();
		ViewController(const ViewController& other);
		ViewController & operator=(const ViewController& other);
		ViewController & operator=(ViewController&& other);
		ViewController(ViewController&& other);

		void ClearScreen();
		void ShowWelcomeScreen();
		const int ShowMenuScreen();
		void ShowCreditScreen();
		void ShowCloseScreen();
		const int ShowOptions(std::vector<std::string> options);
		void ShowMap(const char* const map, unsigned int width, unsigned int height);
		char GetStartScreenInput();
		std::string AskWord(std::string message);
		uint AskInt(std::string message, unsigned int maxInt);
		void Say(const std::string& message);

		void PressAnyKeyToContinue();
	};

} }