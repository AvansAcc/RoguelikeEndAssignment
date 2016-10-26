#include "FileNotFoundException.h"

namespace RogueLike { namespace ErrorHandling {


	FileNotFoundException::FileNotFoundException() noexcept
		: Exception()
	{

	}

	FileNotFoundException::FileNotFoundException(const char* message) noexcept
		: Exception(message)
	{

	}
	FileNotFoundException::FileNotFoundException(std::string message) noexcept
		: Exception(message.c_str())
	{

	}

	FileNotFoundException::~FileNotFoundException() noexcept
	{

	}


	const char* FileNotFoundException::what() const noexcept
	{
		if (!_message.empty())
			return Exception::what();
		else
			return "File not found exception!";
	}

} }