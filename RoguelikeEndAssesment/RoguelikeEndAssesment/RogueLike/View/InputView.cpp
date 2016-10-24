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

	std::string InputView::AskWord(std::string message)
	{
		std::string answer = "";
		std::cout << message << " ";
		std::getline(std::cin, answer);
		return answer;
	}

	uint InputView::AskInt(std::string message)
	{
		int result = 0;
		std::string s = "";
		while (result < 1)
		{
			std::cout << message << " ";
			std::cin >> s;
			try {
				result = FromString<int>(s);
				if (result < 0)
					result = 0;
			}
			catch (...) { result = 0; }
		}
		return result;
	}

} }