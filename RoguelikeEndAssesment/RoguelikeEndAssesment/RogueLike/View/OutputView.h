#pragma once

#include <string>
#include <iostream>

namespace RogueLike { namespace View {
	class OutputView {
	private:
	public:
	
	private:
		std::string GetARoomDescription();

	public:
		OutputView();
		void ShowWelcomScreen();
		void ShowMenu();
		void ShowGame();
		void ShowMap(const char* const map, unsigned int width, unsigned int height);
		void ShowOptions();
		void ShowQuit();
		void Say(const std::string message);
	};
} }