#pragma once
#include <string>
#include "pch.h"
#include "Vertex.h"
#include "IFangSubsystem.h"

using namespace DirectX;
using namespace Fang::Core;

namespace Fang::Rendering
{
	public class FangGraphics : public IFangSubsystem
	{
	public:
		FangGraphics(ISwapChainPanelNative* swapChainPanel, std::wstring shaderCacheLocation);

		HRESULT Start() override {}
		HRESULT Stop() override {}

		HRESULT CreateDeviceResources();
		HRESULT CreateSizeDependentResources(UINT width, UINT height);

		void Render(double deltaTime);

		inline ID3D11DeviceContext* GetDeviceContext() const noexcept { return _deviceContext.p; }
		inline ID3D11Device* GetDevice() const noexcept { return _d3dDevice.p; }

	private:
		std::wstring GetShaderPath(std::wstring shaderName) const;

		template<typename T>
		HRESULT CreateBuffer(D3D11_USAGE usage, D3D11_BIND_FLAG bindFlag, const T* initData, UINT initDataSize, ID3D11Buffer** ppBuffer, D3D11_CPU_ACCESS_FLAG cpuAccessFlags = (D3D11_CPU_ACCESS_FLAG)0)
		{
			if (_d3dDevice == nullptr)
				return ERROR_NOT_READY;

			D3D11_BUFFER_DESC bufferDesc{};
			bufferDesc.Usage = usage;
			bufferDesc.BindFlags = bindFlag;
			bufferDesc.StructureByteStride = sizeof(T);
			bufferDesc.ByteWidth = initDataSize;
			bufferDesc.CPUAccessFlags = cpuAccessFlags;

			D3D11_SUBRESOURCE_DATA subresData{};
			subresData.pSysMem = initData;

			return _d3dDevice->CreateBuffer(&bufferDesc, &subresData, ppBuffer);
		}

		template<typename T>
		inline HRESULT CreateDefaultBuffer(D3D11_BIND_FLAG bindFlag, const T* initData, UINT initDataSize, ID3D11Buffer** ppBuffer)
		{
			return CreateBuffer<T>(D3D11_USAGE_DEFAULT, bindFlag, initData, initDataSize, ppBuffer);
		}
		template<typename T>
		inline HRESULT CreateImmutableBuffer(D3D11_BIND_FLAG bindFlag, const T* initData, UINT initDataSize, ID3D11Buffer** ppBuffer)
		{
			return CreateBuffer<T>(D3D11_USAGE_IMMUTABLE, bindFlag, initData, initDataSize, ppBuffer);
		}
		template<typename T>
		inline HRESULT CreateDynamicBufferWrite(D3D11_BIND_FLAG bindFlag, const T* initData, UINT initDataSize, ID3D11Buffer** ppBuffer)
		{
			return CreateBuffer<T>(D3D11_USAGE_DYNAMIC, bindFlag, initData, initDataSize, ppBuffer, D3D11_CPU_ACCESS_WRITE);
		}
		template<typename T>
		inline HRESULT CreateDynamicBufferRead(D3D11_BIND_FLAG bindFlag, const T* initData, UINT initDataSize, ID3D11Buffer** ppBuffer)
		{
			return CreateBuffer<T>(D3D11_USAGE_DYNAMIC, bindFlag, initData, initDataSize, ppBuffer, D3D11_CPU_ACCESS_READ);
		}
		template<typename T>
		inline HRESULT CreateDynamicBufferReadWrite(D3D11_BIND_FLAG bindFlag, const T* initData, UINT initDataSize, ID3D11Buffer** ppBuffer)
		{
			return CreateBuffer<T>(D3D11_USAGE_DYNAMIC, bindFlag, initData, initDataSize, ppBuffer, D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE);
		}


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

		CComPtr<ID3D11Buffer> _vertexBuff;
		CComPtr<ID3D11Buffer> _indexBuff;

		CComPtr<ID3D11VertexShader> _vertexShader;
		CComPtr<ID3D11PixelShader> _pixelShader;

		CComPtr<ID3D11InputLayout> _inputLayout;

		D3D11_VIEWPORT _viewport{};

		std::wstring _shaderCachePath;
		double _currentTime;

		// temp stuff

		ConstantBuffer _worldTransform;
		float angle;

		CComPtr<ID3D11Buffer> _worldTransformBuffer;
	};

}
