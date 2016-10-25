#pragma once

#include <string>
#include <iostream>
#include "..\Utils\Random.h"

namespace RogueLike { namespace View {
	class OutputView {
	private:

	public:
	
	private:

	public:
		OutputView();
		void ShowWelcomScreen();
		void ShowMenu(std::vector<std::string> menuItems);
		void ShowGame(std::vector<std::string> gameInfo);
		void ShowMap(const char* const map, unsigned int width, unsigned int height);
		void ShowOptions(std::vector<std::string> options);
		void ShowQuit();
		void Say(const std::string message);
	};
} }