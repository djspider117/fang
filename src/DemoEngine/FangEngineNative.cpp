#include "pch.h"
#include "FangEngineNative.h"

namespace Fang::Native
{
	FangEngineNative::FangEngineNative(ISwapChainPanelNative* swapChainPanel)
	{
		_swapChainContainer = swapChainPanel;
	}

	HRESULT FangEngineNative::CreateDeviceResources()
	{
		HRESULT hr = S_OK;
		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		RETURN_FAILED(D3D11CreateDevice(
			NULL, // use default adapter
			D3D_DRIVER_TYPE_HARDWARE, // hardware accelerated, use D3D_DRIVER_TYPE_REFERENCE for testing and validation
			NULL, //software mode, don't use
			flags,
			NULL, // default feature levels: 11, 10.1, 10.0, 9.3, 9.2, 9.1
			0, // count of feature levels array, 0 because of the above,
			D3D11_SDK_VERSION,
			&_d3dDevice, // returned ID3D11Device
			NULL, // out, feature level, don't care,
			&_deviceContext // returned ID3D11DeviceContext 
		));

		RETURN_FAILED(_d3dDevice->QueryInterface<IDXGIDevice2>(&_dxgiDevice));
		RETURN_FAILED(_dxgiDevice->GetAdapter(&_dxgiAdapter));
		RETURN_FAILED(_dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&_dxgiFactory));

		return hr;
	}
	HRESULT FangEngineNative::CreateSizeDependentResources(UINT width, UINT height)
	{
		HRESULT hr = S_OK;

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
		swapChainDesc.Width = width;
		swapChainDesc.Height = height;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.SampleDesc.Count = 1; // no multisampling
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // store apps must use this
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED; // switch to ignore or something else?

		RETURN_FAILED(_dxgiFactory->CreateSwapChainForComposition(
			_d3dDevice,
			&swapChainDesc,
			NULL, //don't restrict content output 
			&_swapChain));

		RETURN_FAILED(_swapChainContainer->SetSwapChain(_swapChain));

		CComPtr<ID3D11Resource> backBuffer;
		RETURN_FAILED(_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&backBuffer));
		RETURN_FAILED(_d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &_rtv));

		return hr;
	}

	void FangEngineNative::Render()
	{
		const float color[] = { 0.4f, 0.1f, 0.9f, 1.0f };
		_deviceContext->ClearRenderTargetView(_rtv, color);

		_swapChain->Present(1, 0);
	}
}