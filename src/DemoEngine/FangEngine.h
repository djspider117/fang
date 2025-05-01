#pragma once

#include "FangEngineNative.h"

using namespace System;

namespace Fang
{
	public ref class FangEngine
	{
	public:
		FangEngine(IntPtr^ swapChainPanelNativePtr);
		~FangEngine();

		void Initialize(UINT initialWidth, UINT initialHeight);

	private:
		IntPtr^ _swapChainPanelNativePtr;
		Fang::Native::FangEngineNative* _engine;
	};


}

void ThrowIfFailed(HRESULT hr, String^ msg);
void ThrowIfFailed(HRESULT hr);