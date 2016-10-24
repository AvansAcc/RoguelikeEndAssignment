#include "OutputView.h"

namespace RogueLike { namespace View {

	OutputView::OutputView()
	{
		// Nothing to see here..
	}

	void OutputView::ShowWelcomScreen()
	{
		std::cout << "Welkom bij Kerkers en draken vreemdeling" << std::endl;
	}

	void OutputView::ShowMenu(std::vector<std::string> menuItems)
	{
		for (int i = 0; i < menuItems.size(); i++)
		{
			std::cout << (i + 1) << ":  " << menuItems[i] << std::endl;
		}
	}

	void OutputView::ShowMap(const char* const map, unsigned int width, unsigned int height)
	{
		int dimension = (width * 4 - 3) * (height * 2 - 1);
		if (map != nullptr)
		{
			for (int i = 0; i < dimension; i++)
			{
				std::cout << ((i % (width * 4 - 3) == 0) ? "\n" : "") << map[i];
			}
			std::cout << std::endl;
		}
	}

	std::string OutputView::GetARoomDescription()
	{
		return "";
	}

	void OutputView::ShowGame()
	{
		std::cout << "(Show Game)" << std::endl;
	}

	void OutputView::ShowOptions(std::vector<std::string> options)
	{
		std::cout << "Kies wat je wilt doen door het bijbehorende getal mee te geven:" << std::endl;
		for (int i = 0; i < options.size(); i++)
		{
			std::cout << (i + 1) << ":  " << options[i] << std::endl;
		}
	}

	void OutputView::ShowQuit()
	{
		std::cout << std::endl;
		std::cout << "Jammer dat je weggaat!" << std::endl;
		std::cout << "Tot de volgende keer!" << std::endl;
	}

	void OutputView::Say(const std::string message)
	{
		std::cout << message;
	}

} }