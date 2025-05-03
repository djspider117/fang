#include "pch.h"
#include "FangEngine.h"
#include "FangDev.h"
#include <msclr/marshal_cppstd.h>

namespace Fang
{
	FangEngine::FangEngine(IntPtr^ swapChainPanelNativePtr, String^ shaderCacheLocation) :
		_swapChainPanelNativePtr(reinterpret_cast<ISwapChainPanelNative*>(swapChainPanelNativePtr->ToPointer())),
		_shaderCacheLocation(shaderCacheLocation) {
	}

	FangEngine::~FangEngine()
	{
		_initialized = false;
		delete _graphicsSubsystem;
	}

	void FangEngine::Initialize(UINT width, UINT height)
	{
		msclr::interop::marshal_context context;
		_graphicsSubsystem = new FangGraphics(_swapChainPanelNativePtr, context.marshal_as<std::wstring>(_shaderCacheLocation));

		ThrowIfFailed(_graphicsSubsystem->CreateDeviceResources());
		ThrowIfFailed(_graphicsSubsystem->CreateSizeDependentResources(width, height));

		_initialized = true;
	}

	void FangEngine::HandleSizeChanged(UINT width, UINT height)
	{
		// memory leaks here
		_initialized = false;

		ThrowIfFailed(_graphicsSubsystem->Stop());
		delete _graphicsSubsystem;
		_graphicsSubsystem = nullptr;

		Initialize(width, height);
	}

	void FangEngine::Tick(double deltaTime)
	{
		if (!_initialized)
			return;

		_graphicsSubsystem->Render(deltaTime);
	}
}