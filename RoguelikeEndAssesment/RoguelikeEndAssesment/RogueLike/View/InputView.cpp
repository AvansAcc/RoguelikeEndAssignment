#include "InputView.h"

namespace RogueLike { namespace View {

	InputView::InputView()
	{
		// Nothing to see here..
	}


	char InputView::AskLetter()
	{
		char answer = 0;
		answer = std::getchar();
		return answer;
	}

	std::string InputView::AskWord()
	{
		std::string answer = "";
		std::getline(std::cin, answer);
		return answer;
	}

} }