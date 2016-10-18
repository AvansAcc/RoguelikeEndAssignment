#pragma once

#include <iostream>
#include <string>
#include "../Common.h"

namespace RogueLike { namespace View {
	class InputView {
	private:
	public:

	private:
	public:
		InputView();
	
		char AskLetter();
		std::string AskWord();
		uint AskInt(std::string message);
	};
} }