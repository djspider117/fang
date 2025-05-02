#include "FangDev.h"
#include "pch.h"
#include "FangException.h"

void ThrowIfFailed(HRESULT hr, String^ msg)
{
	if (FAILED(hr))
	{
		auto inner = System::Runtime::InteropServices::Marshal::GetExceptionForHR(hr);
		throw gcnew Fang::FangException(msg, inner);
	}
}

void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
		System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(hr);
}