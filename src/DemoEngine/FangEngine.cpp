#include "pch.h"
#include "FangEngine.h"

using namespace Fang::Native;

namespace Fang
{
	FangEngine::FangEngine(IntPtr^ swapChainPanelNativePtr) :
		_swapChainPanelNativePtr(swapChainPanelNativePtr)
	{
		auto nativeSwapChainPanel = reinterpret_cast<ISwapChainPanelNative*>(swapChainPanelNativePtr->ToPointer());
		_engine = new FangEngineNative(nativeSwapChainPanel);
	}

	FangEngine::~FangEngine()
	{
		delete _engine;
	}

	void FangEngine::Initialize(UINT initialWidth, UINT initialHeight)
	{
		ThrowIfFailed(_engine->CreateDeviceResources());
		ThrowIfFailed(_engine->CreateSizeDependentResources(initialWidth, initialHeight));

		_engine->Render();
	}

	void FangEngine::Render()
	{
		_engine->Render();
	}
}

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
