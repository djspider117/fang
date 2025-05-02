#pragma once

using namespace System;

namespace Fang
{
	public ref class FangException : public Exception
	{
	public:
		FangException(String^ message) : Exception(message) { }
		FangException(String^ message, Exception^ inner) : Exception(message, inner) {}
	};
}