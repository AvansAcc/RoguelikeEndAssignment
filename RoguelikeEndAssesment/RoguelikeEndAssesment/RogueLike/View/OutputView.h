#pragma once

#include <string>

namespace RogueLike { namespace View {
	class OutputView {
	public:
		std::string GetARoomDescription();
		void ShowMenu();
		void ShowGame();
		void ShowOptions();
	};
} }