#pragma once
#include "../View/InputView.h"
#include "../View/OutputView.h"

namespace RogueLike { namespace Controller {

	class ViewController {
	private:
		View::InputView* _inputView;
		View::OutputView* _outputView;
	public:

	private:
	public:
		ViewController();
		~ViewController();
		ViewController(const ViewController& other);
		ViewController & operator=(const ViewController& other);
		ViewController & operator=(ViewController&& other);
		ViewController(ViewController&& other);
	};

} }