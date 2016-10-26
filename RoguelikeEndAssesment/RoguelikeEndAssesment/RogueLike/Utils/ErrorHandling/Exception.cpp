#include "Exception.h"

namespace RogueLike { namespace Utils { namespace ErrorHandling {


	Exception::Exception() noexcept
		: std::exception()
	{
		_message = std::exception::what();
	}

	Exception::Exception(const char* message) noexcept
		: std::exception(message)
	{
		_message = message;
	}
	Exception::Exception(std::string message) noexcept
		: std::exception(message.c_str())
	{
		_message = message;
	}

	Exception::~Exception() noexcept { }


	const char* Exception::what() const noexcept
	{
		if (!_message.empty())
			return _message.c_str();
		else
			return "Unknown exception.";
	}

	Exception::Exception(const Exception& other) noexcept { }
	Exception::Exception(Exception&& other) noexcept { }
	Exception& Exception::operator=(const Exception& other) noexcept 
	{
		if (this != &other)
		{
			// copy fields
		}
		return *this;
	}
	Exception& Exception::operator=(Exception&& other) noexcept
	{
		if (this != &other)
		{
			// move fields
		}
		return *this;
	}

} } }