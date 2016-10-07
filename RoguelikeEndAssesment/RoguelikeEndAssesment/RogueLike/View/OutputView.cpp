#include "OutputView.h"

namespace RogueLike { namespace View {

	OutputView::OutputView()
	{

	}

	std::string OutputView::GetARoomDescription()
	{
		return "";
	}

	void OutputView::ShowMenu()
	{
		std::cout << "Show Menu" << std::endl;
	}
	void OutputView::ShowGame()
	{
		std::cout << "Show Game" << std::endl;
	}
	void OutputView::ShowOptions()
	{
		std::cout << "Show Options" << std::endl;
	}

} }