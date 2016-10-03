#pragma once
#include "../View/InputView.h"
#include "../View/OutputView.h"

namespace RogueLike { namespace Controller {

	class ViewController {
	private:
		View::InputView _inputView;
		View::OutputView _outputView;
	};

} }