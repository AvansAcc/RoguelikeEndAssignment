#pragma once

#include <string>
#include "Exception.h"

namespace RogueLike { namespace Utils { namespace ErrorHandling {

	class FileNotFoundException : public Exception {
	private:

	public:
		FileNotFoundException() noexcept;
		FileNotFoundException(const char* message) noexcept;
		FileNotFoundException(std::string message) noexcept;
		virtual ~FileNotFoundException() noexcept;

		virtual const char* what() const noexcept;
	};

} } }