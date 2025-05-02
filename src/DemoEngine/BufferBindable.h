#pragma once
#include "pch.h"
#include "IFangBindable.h"

namespace Fang::Rendering::Bindables
{

	public class BufferBindable : public IFangBindable
	{
	public:
		template<typename T>
		HRESULT CreateBuffer(ID3D11Device* device, D3D11_USAGE usage, D3D11_BIND_FLAG bindFlag, const T* initData, UINT initDataSize, ID3D11Buffer** ppBuffer, D3D11_CPU_ACCESS_FLAG cpuAccessFlags = (D3D11_CPU_ACCESS_FLAG)0)
		{
			if (device == nullptr)
				return ERROR_NOT_READY;

			D3D11_BUFFER_DESC bufferDesc{};
			bufferDesc.Usage = usage;
			bufferDesc.BindFlags = bindFlag;
			bufferDesc.StructureByteStride = sizeof(T);
			bufferDesc.ByteWidth = initDataSize;
			bufferDesc.CPUAccessFlags = cpuAccessFlags;

			D3D11_SUBRESOURCE_DATA subresData{};
			subresData.pSysMem = initData;

			return device->CreateBuffer(&bufferDesc, &subresData, ppBuffer);
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

	protected:
		CComPtr<ID3D11Buffer> _buffer;
	};

}