#include "Exception.h"

namespace RogueLike { namespace Utils { namespace ErrorHandling {


	Exception::Exception() 
		: std::exception()
	{

	}

	const char* Exception::what() const noexcept
	{
		return std::exception::what();
	}



} } }