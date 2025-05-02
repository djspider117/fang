#pragma once

#include "FangGraphics.h"

using namespace System;
using namespace Fang::Core;
using namespace Fang::Rendering;

namespace Fang
{
	public ref class FangEngine
	{
	public:
		FangEngine(IntPtr^ swapChainPanelNativePtr, String^ shaderCacheLocation);
		~FangEngine();

		void Initialize(UINT initialWidth, UINT initialHeight);
		void HandleSizeChanged(UINT initialWidth, UINT initialHeight);

		void Tick(double deltaTime);

	private:
		ISwapChainPanelNative* _swapChainPanelNativePtr;
		String^ _shaderCacheLocation;
		FangGraphics* _graphicsSubsystem;

		bool _initialized;
	};
};