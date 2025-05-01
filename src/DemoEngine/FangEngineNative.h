#pragma once
#include "pch.h"

namespace Fang::Native
{
	public class FangEngineNative
	{
	public:
		FangEngineNative(ISwapChainPanelNative* swapChainPanel);

		HRESULT CreateDeviceResources();
		HRESULT CreateSizeDependentResources(UINT width, UINT height);

		void Render();

	private:
		CComPtr<ISwapChainPanelNative> _swapChainContainer;
		CComPtr<ID3D11Device> _d3dDevice;
		CComPtr<IDXGIDevice2> _dxgiDevice;
		CComPtr<IDXGIAdapter> _dxgiAdapter;
		CComPtr<IDXGIFactory2> _dxgiFactory;
		CComPtr<ID3D11DeviceContext> _deviceContext;
		CComPtr<IDXGISwapChain1> _swapChain;
		CComPtr<ID3D11RenderTargetView> _rtv;
	};
}
