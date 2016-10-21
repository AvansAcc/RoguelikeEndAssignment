#include "OutputView.h"

namespace RogueLike { namespace View {

	OutputView::OutputView()
	{
		// Nothing to see here..
	}

	void OutputView::ShowWelcomScreen()
	{
		std::cout << "Welkom vreemdeling! Welkom bij onze geweldige game, Kerkers en Draken!" << std::endl;
	}
	void OutputView::ShowMap(char* map, unsigned int width, unsigned int height)
	{
		for (unsigned int i = 0; i < width * height; i++)
		{
			std::cout << ((i % width == 0) ? "\n" : " ") << map[i];
		}
		std::cout << std::endl;
	}

	std::string OutputView::GetARoomDescription()
	{
		return "";
	}

	void OutputView::ShowMenu()
	{
		std::cout << "(Show Menu)" << std::endl;
	}
	void OutputView::ShowGame()
	{
		std::cout << "(Show Game)" << std::endl;
	}
	void OutputView::ShowOptions()
	{
		std::cout << "(Show Options)" << std::endl;
	}

	void OutputView::ShowQuit()
	{
		std::cout << "Jammer dat je weggaat!" << std::endl;
		std::cout << "Tot de volgende keer!" << std::endl;
	}

	void OutputView::Say(const std::string message)
	{
		std::cout << message;
	}

} }