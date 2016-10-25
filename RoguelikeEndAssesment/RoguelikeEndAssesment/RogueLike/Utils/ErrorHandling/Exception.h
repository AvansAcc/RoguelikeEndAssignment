#pragma once
#include <string>
#include <exception>
#include <iostream>

namespace RogueLike { namespace Utils { namespace ErrorHandling {

	class Exception : public std::exception {
	protected:
		std::string _message;
	public:
		Exception() noexcept;
		Exception(const char* message) noexcept;
		Exception(std::string message) noexcept;
		Exception(const Exception& other) noexcept;
		Exception(Exception&& other) noexcept;
		Exception& operator=(const Exception& other) noexcept;
		Exception& operator=(Exception&& other) noexcept;
		virtual ~Exception() noexcept;

		virtual const char* what() const noexcept;
	};

} } }