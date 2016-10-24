#pragma once

#include <string>
#include <iostream>
#include "..\Utils\Random.h"

namespace RogueLike { namespace View {
	class OutputView {
	private:

	public:
	
	private:
		std::string GetARoomDescription();

	public:
		OutputView();
		void ShowWelcomScreen();
		void ShowMenu(std::vector<std::string> menuItems);
		void ShowGame();
		void ShowMap(const char* const map, unsigned int width, unsigned int height);
		void ShowOptions(std::vector<std::string> options);
		void ShowQuit();
		void Say(const std::string message);
	};
} }