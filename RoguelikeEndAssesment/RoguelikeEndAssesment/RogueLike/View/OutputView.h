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
		void ShowMenu();
		void ShowGame();
		void ShowOptions();
	};
} }