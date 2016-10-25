#pragma once

#include <exception>

namespace RogueLike { namespace Utils { namespace ErrorHandling {

	class Exception : public std::exception {

	public:
		Exception() noexcept;
		Exception(const Exception& exp) noexcept;
		Exception(Exception&& exp) noexcept;
		Exception& operator=(const Exception& exp) noexcept;
		Exception& operator=(Exception&& exp) noexcept;
		virtual ~Exception() noexcept;

		virtual const char* what() const noexcept;
	};

} } }