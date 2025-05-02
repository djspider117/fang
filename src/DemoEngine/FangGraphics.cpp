#include "pch.h"
#include "FangGraphics.h"
#include "Vertex.h"
#include "DrawableBase.h"

namespace Fang::Rendering
{
	FangGraphics::FangGraphics(ISwapChainPanelNative* swapChainPanel, std::wstring shaderCacheLocation) :
		_swapChainContainer(swapChainPanel),
		_shaderCachePath(shaderCacheLocation)
	{
		_worldTransform.transform = DirectX::XMMatrixIdentity();
	}

	HRESULT FangGraphics::CreateDeviceResources()
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

		RETURN_FAILED(Fang::Rendering::Drawables::CreateDemoDrawable(*this, &_demo));

		return hr;
	}
	HRESULT FangGraphics::CreateSizeDependentResources(UINT width, UINT height)
	{
		HRESULT hr = S_OK;

		_viewport.Width = width;
		_viewport.Height = height;
		_viewport.MinDepth = 0;
		_viewport.MaxDepth = 1;
		_viewport.TopLeftX = 0;
		_viewport.TopLeftY = 0;

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

		D3D11_DEPTH_STENCIL_DESC depthDesc{};
		depthDesc.DepthEnable = true;
		depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

		RETURN_FAILED(_d3dDevice->CreateDepthStencilState(&depthDesc, &_depthStencilState));

		D3D11_TEXTURE2D_DESC depthTextureDesc{};
		depthTextureDesc.Width = width;
		depthTextureDesc.Height = height;
		depthTextureDesc.MipLevels = 1;
		depthTextureDesc.ArraySize = 1;
		depthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthTextureDesc.SampleDesc.Count = 1;
		depthTextureDesc.SampleDesc.Quality = 0;
		depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		RETURN_FAILED(_d3dDevice->CreateTexture2D(&depthTextureDesc, nullptr, &_depthStencil));

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		RETURN_FAILED(_d3dDevice->CreateDepthStencilView(_depthStencil, &dsvDesc, &_dsv));

		_deviceContext->OMSetDepthStencilState(_depthStencilState, 0);

		return hr;
	}

	void FangGraphics::Render(double deltaTime)
	{
		_currentTime += deltaTime;
		// simulation
		angle = sin(_currentTime) * 40;
		
		/*_worldTransform.transform = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationZ(angle) * DirectX::XMMatrixPerspectiveLH(1, _viewport.Height / _viewport.Width, 0.03f, 10.0f));
		
		_deviceContext->UpdateSubresource(_worldTransformBuffer, 0, nullptr, &_worldTransform, 0, 0);*/

		// render
		const float color[] = { 0.4f, 0.1f, 0.9f, 1.0f };
		_deviceContext->ClearRenderTargetView(_rtv, color);
		_deviceContext->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);

		const UINT stride = sizeof(Vertex);
		const UINT offset = 0;

		//DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL forces us to rebind the rtv and the dsv
		_deviceContext->OMSetRenderTargets(1, &(_rtv.p), _dsv);
		_deviceContext->RSSetViewports(1, &_viewport);

		_demo->Draw(*this);

		_deviceContext->DrawIndexed(36, 0, 0);

		_swapChain->Present(1, 0);
	}

	std::wstring FangGraphics::GetShaderPath(std::wstring shaderName) const
	{
		if (_shaderCachePath.back() != '\\')
			return _shaderCachePath + L"\\" + shaderName;

		return _shaderCachePath + shaderName;
	}
}