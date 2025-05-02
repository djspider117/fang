#pragma once

#include <Windows.h>
#include <exception>
#include <system_error>

using namespace System;

namespace Fang::Core
{
	public class HResultException : public std::exception
	{
	public:
		HResultException(HRESULT hr) :
			_hr(hr),
			exception(std::system_category().message(hr).c_str())
		{
		}

	private:
		HRESULT _hr;
	};
}