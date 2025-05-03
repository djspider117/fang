#pragma once
#include <string>
#include "pch.h"
#include "Vertex.h"
#include "IFangSubsystem.h"

using namespace DirectX;
using namespace Fang::Core;

namespace Fang::Rendering::Drawables
{
	class DemoCube;
}

namespace Fang::Rendering
{
	public class FangGraphics : public IFangSubsystem
	{
	public:
		FangGraphics(ISwapChainPanelNative* swapChainPanel, std::wstring shaderCacheLocation);

		HRESULT Start() override { return S_OK; }
		HRESULT Stop() override { return S_OK; }

		HRESULT CreateDeviceResources();
		HRESULT CreateSizeDependentResources(UINT width, UINT height);

		void Render(double deltaTime);

		inline ID3D11DeviceContext* GetContext() const noexcept { return _deviceContext.p; }
		inline ID3D11Device* GetDevice() const noexcept { return _d3dDevice.p; }
		inline DirectX::XMMATRIX GetProjectionMatrix() const noexcept { return _projectionMatrix; }

		std::wstring GetShaderPath(std::wstring shaderName) const;
	private:

		CComPtr<ISwapChainPanelNative> _swapChainContainer;
		CComPtr<ID3D11Device> _d3dDevice;
		CComPtr<IDXGIDevice2> _dxgiDevice;
		CComPtr<IDXGIAdapter> _dxgiAdapter;
		CComPtr<IDXGIFactory2> _dxgiFactory;
		CComPtr<ID3D11DeviceContext> _deviceContext;
		CComPtr<IDXGISwapChain1> _swapChain;
		CComPtr<ID3D11RenderTargetView> _rtv;

		CComPtr<ID3D11DepthStencilState> _depthStencilState;
		CComPtr<ID3D11DepthStencilView> _dsv;
		CComPtr<ID3D11Texture2D> _depthStencil;

		D3D11_VIEWPORT _viewport{};
		DirectX::XMMATRIX _projectionMatrix;

		std::wstring _shaderCachePath;
		double _currentTime;

		// temp stuff

		Drawables::DemoCube* _demo;
		float angle;

		CComPtr<ID3D11Buffer> _worldTransformBuffer;
	};

}
